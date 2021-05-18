#include "CodeGenIntrinsics.h"
#include "llvm/TableGen/Error.h"
#include "llvm/TableGen/Record.h"

namespace llvm {

MVT::SimpleValueType getValueType(Record *Rec) {
  return (MVT::SimpleValueType)Rec->getValueAsInt("Value");
}

//===----------------------------------------------------------------------===//
// CodeGenIntrinsic Implementation
//===----------------------------------------------------------------------===//

CodeGenIntrinsicTable::CodeGenIntrinsicTable(const RecordKeeper &RC) {
  std::vector<Record *> IntrProperties =
      RC.getAllDerivedDefinitions("IntrinsicProperty");

  std::vector<Record *> DefaultProperties;
  for (Record *Rec : IntrProperties)
    if (Rec->getValueAsBit("IsDefault"))
      DefaultProperties.push_back(Rec);

  std::vector<Record *> Defs = RC.getAllDerivedDefinitions("Intrinsic");
  Intrinsics.reserve(Defs.size());

  for (unsigned I = 0, e = Defs.size(); I != e; ++I)
    Intrinsics.push_back(CodeGenIntrinsic(Defs[I], DefaultProperties));

  llvm::sort(Intrinsics,
             [](const CodeGenIntrinsic &LHS, const CodeGenIntrinsic &RHS) {
               return std::tie(LHS.TargetPrefix, LHS.Name) <
                      std::tie(RHS.TargetPrefix, RHS.Name);
             });
  Targets.push_back({"", 0, 0});
  for (size_t I = 0, E = Intrinsics.size(); I < E; ++I)
    if (Intrinsics[I].TargetPrefix != Targets.back().Name) {
      Targets.back().Count = I - Targets.back().Offset;
      Targets.push_back({Intrinsics[I].TargetPrefix, I, 0});
    }
  Targets.back().Count = Intrinsics.size() - Targets.back().Offset;
}

CodeGenIntrinsic::CodeGenIntrinsic(Record *R,
                                   std::vector<Record *> DefaultProperties) {
  TheDef = R;
  std::string DefName = std::string(R->getName());
  ArrayRef<SMLoc> DefLoc = R->getLoc();
  ModRef = ReadWriteMem;
  Properties = 0;
  isOverloaded = false;
  isCommutative = false;
  canThrow = false;
  isNoReturn = false;
  isNoSync = false;
  isNoFree = false;
  isWillReturn = false;
  isCold = false;
  isNoDuplicate = false;
  isConvergent = false;
  isSpeculatable = false;
  hasSideEffects = false;

  if (DefName.size() <= 4 ||
      std::string(DefName.begin(), DefName.begin() + 4) != "int_")
    PrintFatalError(DefLoc,
                    "Intrinsic '" + DefName + "' does not start with 'int_'!");

  EnumName = std::string(DefName.begin()+4, DefName.end());

  if (R->getValue("GCCBuiltinName"))  // Ignore a missing GCCBuiltinName field.
    GCCBuiltinName = std::string(R->getValueAsString("GCCBuiltinName"));
  if (R->getValue("MSBuiltinName"))   // Ignore a missing MSBuiltinName field.
    MSBuiltinName = std::string(R->getValueAsString("MSBuiltinName"));

  TargetPrefix = std::string(R->getValueAsString("TargetPrefix"));
  Name = std::string(R->getValueAsString("LLVMName"));

  if (Name == "") {
    // If an explicit name isn't specified, derive one from the DefName.
    Name = "llvm.";

    for (unsigned i = 0, e = EnumName.size(); i != e; ++i)
      Name += (EnumName[i] == '_') ? '.' : EnumName[i];
  } else {
    // Verify it starts with "llvm.".
    if (Name.size() <= 5 ||
        std::string(Name.begin(), Name.begin() + 5) != "llvm.")
      PrintFatalError(DefLoc, "Intrinsic '" + DefName +
                                  "'s name does not start with 'llvm.'!");
  }

  // If TargetPrefix is specified, make sure that Name starts with
  // "llvm.<targetprefix>.".
  if (!TargetPrefix.empty()) {
    if (Name.size() < 6+TargetPrefix.size() ||
        std::string(Name.begin() + 5, Name.begin() + 6 + TargetPrefix.size())
        != (TargetPrefix + "."))
      PrintFatalError(DefLoc, "Intrinsic '" + DefName +
                                  "' does not start with 'llvm." +
                                  TargetPrefix + ".'!");
  }

  ListInit *RetTypes = R->getValueAsListInit("RetTypes");
  ListInit *ParamTypes = R->getValueAsListInit("ParamTypes");

  // First collate a list of overloaded types.
  std::vector<MVT::SimpleValueType> OverloadedVTs;
  for (ListInit *TypeList : {RetTypes, ParamTypes}) {
    for (unsigned i = 0, e = TypeList->size(); i != e; ++i) {
      Record *TyEl = TypeList->getElementAsRecord(i);
      assert(TyEl->isSubClassOf("LLVMType") && "Expected a type!");

      if (TyEl->isSubClassOf("LLVMMatchType"))
        continue;

      MVT::SimpleValueType VT = getValueType(TyEl->getValueAsDef("VT"));
      if (MVT(VT).isOverloaded()) {
        OverloadedVTs.push_back(VT);
        isOverloaded = true;
      }
    }
  }

  // Parse the list of return types.
  ListInit *TypeList = RetTypes;
  for (unsigned i = 0, e = TypeList->size(); i != e; ++i) {
    Record *TyEl = TypeList->getElementAsRecord(i);
    assert(TyEl->isSubClassOf("LLVMType") && "Expected a type!");
    MVT::SimpleValueType VT;
    if (TyEl->isSubClassOf("LLVMMatchType")) {
      unsigned MatchTy = TyEl->getValueAsInt("Number");
      assert(MatchTy < OverloadedVTs.size() &&
             "Invalid matching number!");
      VT = OverloadedVTs[MatchTy];
      // It only makes sense to use the extended and truncated vector element
      // variants with iAny types; otherwise, if the intrinsic is not
      // overloaded, all the types can be specified directly.
      assert(((!TyEl->isSubClassOf("LLVMExtendedType") &&
               !TyEl->isSubClassOf("LLVMTruncatedType")) ||
              VT == MVT::iAny || VT == MVT::vAny) &&
             "Expected iAny or vAny type");
    } else {
      VT = getValueType(TyEl->getValueAsDef("VT"));
    }

    // Reject invalid types.
    if (VT == MVT::isVoid)
      PrintFatalError(DefLoc, "Intrinsic '" + DefName +
                                  " has void in result type list!");

    IS.RetVTs.push_back(VT);
    IS.RetTypeDefs.push_back(TyEl);
  }

  // Parse the list of parameter types.
  TypeList = ParamTypes;
  for (unsigned i = 0, e = TypeList->size(); i != e; ++i) {
    Record *TyEl = TypeList->getElementAsRecord(i);
    assert(TyEl->isSubClassOf("LLVMType") && "Expected a type!");
    MVT::SimpleValueType VT;
    if (TyEl->isSubClassOf("LLVMMatchType")) {
      unsigned MatchTy = TyEl->getValueAsInt("Number");
      if (MatchTy >= OverloadedVTs.size()) {
        PrintError(R->getLoc(),
                   "Parameter #" + Twine(i) + " has out of bounds matching "
                   "number " + Twine(MatchTy));
        PrintFatalError(DefLoc,
                        Twine("ParamTypes is ") + TypeList->getAsString());
      }
      VT = OverloadedVTs[MatchTy];
      // It only makes sense to use the extended and truncated vector element
      // variants with iAny types; otherwise, if the intrinsic is not
      // overloaded, all the types can be specified directly.
      assert(((!TyEl->isSubClassOf("LLVMExtendedType") &&
               !TyEl->isSubClassOf("LLVMTruncatedType")) ||
              VT == MVT::iAny || VT == MVT::vAny) &&
             "Expected iAny or vAny type");
    } else
      VT = getValueType(TyEl->getValueAsDef("VT"));

    // Reject invalid types.
    if (VT == MVT::isVoid && i != e-1 /*void at end means varargs*/)
      PrintFatalError(DefLoc, "Intrinsic '" + DefName +
                                  " has void in result type list!");

    IS.ParamVTs.push_back(VT);
    IS.ParamTypeDefs.push_back(TyEl);
  }

  // Parse the intrinsic properties.
  ListInit *PropList = R->getValueAsListInit("IntrProperties");
  for (unsigned i = 0, e = PropList->size(); i != e; ++i) {
    Record *Property = PropList->getElementAsRecord(i);
    assert(Property->isSubClassOf("IntrinsicProperty") &&
           "Expected a property!");

    setProperty(Property);
  }

  // Set default properties to true.
  setDefaultProperties(R, DefaultProperties);

  // Also record the SDPatternOperator Properties.
  Properties = parseSDPatternOperatorProperties(R);

  // Sort the argument attributes for later benefit.
  llvm::sort(ArgumentAttributes);
}

void CodeGenIntrinsic::setDefaultProperties(
    Record *R, std::vector<Record *> DefaultProperties) {
  // opt-out of using default attributes.
  if (R->getValueAsBit("DisableDefaultAttributes"))
    return;

  for (Record *Rec : DefaultProperties)
    setProperty(Rec);
}

void CodeGenIntrinsic::setProperty(Record *R) {
  if (R->getName() == "IntrNoMem")
    ModRef = NoMem;
  else if (R->getName() == "IntrReadMem") {
    if (!(ModRef & MR_Ref))
      PrintFatalError(TheDef->getLoc(),
                      Twine("IntrReadMem cannot be used after IntrNoMem or "
                            "IntrWriteMem. Default is ReadWrite"));
    ModRef = ModRefBehavior(ModRef & ~MR_Mod);
  } else if (R->getName() == "IntrWriteMem") {
    if (!(ModRef & MR_Mod))
      PrintFatalError(TheDef->getLoc(),
                      Twine("IntrWriteMem cannot be used after IntrNoMem or "
                            "IntrReadMem. Default is ReadWrite"));
    ModRef = ModRefBehavior(ModRef & ~MR_Ref);
  } else if (R->getName() == "IntrArgMemOnly")
    ModRef = ModRefBehavior((ModRef & ~MR_Anywhere) | MR_ArgMem);
  else if (R->getName() == "IntrInaccessibleMemOnly")
    ModRef = ModRefBehavior((ModRef & ~MR_Anywhere) | MR_InaccessibleMem);
  else if (R->getName() == "IntrInaccessibleMemOrArgMemOnly")
    ModRef = ModRefBehavior((ModRef & ~MR_Anywhere) | MR_ArgMem |
                            MR_InaccessibleMem);
  else if (R->getName() == "Commutative")
    isCommutative = true;
  else if (R->getName() == "Throws")
    canThrow = true;
  else if (R->getName() == "IntrNoDuplicate")
    isNoDuplicate = true;
  else if (R->getName() == "IntrConvergent")
    isConvergent = true;
  else if (R->getName() == "IntrNoReturn")
    isNoReturn = true;
  else if (R->getName() == "IntrNoSync")
    isNoSync = true;
  else if (R->getName() == "IntrNoFree")
    isNoFree = true;
  else if (R->getName() == "IntrWillReturn")
    isWillReturn = !isNoReturn;
  else if (R->getName() == "IntrCold")
    isCold = true;
  else if (R->getName() == "IntrSpeculatable")
    isSpeculatable = true;
  else if (R->getName() == "IntrHasSideEffects")
    hasSideEffects = true;
  else if (R->isSubClassOf("NoCapture")) {
    unsigned ArgNo = R->getValueAsInt("ArgNo");
    ArgumentAttributes.emplace_back(ArgNo, NoCapture, 0);
  } else if (R->isSubClassOf("NoAlias")) {
    unsigned ArgNo = R->getValueAsInt("ArgNo");
    ArgumentAttributes.emplace_back(ArgNo, NoAlias, 0);
  } else if (R->isSubClassOf("NoUndef")) {
    unsigned ArgNo = R->getValueAsInt("ArgNo");
    ArgumentAttributes.emplace_back(ArgNo, NoUndef, 0);
  } else if (R->isSubClassOf("Returned")) {
    unsigned ArgNo = R->getValueAsInt("ArgNo");
    ArgumentAttributes.emplace_back(ArgNo, Returned, 0);
  } else if (R->isSubClassOf("ReadOnly")) {
    unsigned ArgNo = R->getValueAsInt("ArgNo");
    ArgumentAttributes.emplace_back(ArgNo, ReadOnly, 0);
  } else if (R->isSubClassOf("WriteOnly")) {
    unsigned ArgNo = R->getValueAsInt("ArgNo");
    ArgumentAttributes.emplace_back(ArgNo, WriteOnly, 0);
  } else if (R->isSubClassOf("ReadNone")) {
    unsigned ArgNo = R->getValueAsInt("ArgNo");
    ArgumentAttributes.emplace_back(ArgNo, ReadNone, 0);
  } else if (R->isSubClassOf("ImmArg")) {
    unsigned ArgNo = R->getValueAsInt("ArgNo");
    ArgumentAttributes.emplace_back(ArgNo, ImmArg, 0);
  } else if (R->isSubClassOf("Align")) {
    unsigned ArgNo = R->getValueAsInt("ArgNo");
    uint64_t Align = R->getValueAsInt("Align");
    ArgumentAttributes.emplace_back(ArgNo, Alignment, Align);
  } else
    llvm_unreachable("Unknown property!");
}

bool CodeGenIntrinsic::isParamAPointer(unsigned ParamIdx) const {
  if (ParamIdx >= IS.ParamVTs.size())
    return false;
  MVT ParamType = MVT(IS.ParamVTs[ParamIdx]);
  return ParamType == MVT::iPTR || ParamType == MVT::iPTRAny;
}

bool CodeGenIntrinsic::isParamImmArg(unsigned ParamIdx) const {
  // Convert argument index to attribute index starting from `FirstArgIndex`.
  ArgAttribute Val{ParamIdx + 1, ImmArg, 0};
  return std::binary_search(ArgumentAttributes.begin(),
                            ArgumentAttributes.end(), Val);
}
} // llvm

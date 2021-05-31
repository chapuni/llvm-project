set(LLVM_ENABLE_TABLEGEN_MODULARIZED ON)

add_tablegen(llvm-tblgen LLVM
  TableGen.cpp

  MODULE attrs
  Attributes.cpp

  MODULE ctags
  CTagsEmitter.cpp

  MODULE exegesis
  ExegesisEmitter.cpp

  MODULE opt-rst
  OptEmitter.cpp
  OptRSTEmitter.cpp
  SHARED

  MODULE opt-parser-defs
  OptParserEmitter.cpp
  DEPENDS opt-rst

  MODULE directive-decl
  DirectiveEmitter.cpp
  GenDirectivesEnumDecl.cpp
  SHARED

  MODULE directive-gen
  GenDirectivesEnumGen.cpp
  DEPENDS directive-decl

  MODULE directive-impl
  GenDirectivesEnumImpl.cpp
  DEPENDS directive-decl

  MODULE automata
  DFAEmitter.cpp
  SHARED

  MODULE intrinsic-enums
  CodeGenIntrinsics.cpp
  IntrinsicEnumsEmitter.cpp
  SDNodeProperties.cpp
  SHARED

  MODULE searchable-tables
  SearchableTableEmitter.cpp
  DEPENDS intrinsic-enums

  MODULE intrinsic-impl
  EmitLongStrLiterals.cpp
  IntrinsicImplEmitter.cpp
  DEPENDS intrinsic-enums
  SHARED

  MODULE callingconv
  CallingConvEmitter.cpp
  CodeGenHwModes.cpp
  CodeGenInstruction.cpp
  CodeGenRegisters.cpp
  CodeGenSchedule.cpp
  CodeGenTarget.cpp
  InfoByHwMode.cpp
  DEPENDS intrinsic-enums
  SHARED

  MODULE x86-EVEX2VEX-tables
  X86EVEX2VEXTablesEmitter.cpp
  DEPENDS callingconv

  MODULE pseudo-lowering
  PseudoLoweringEmitter.cpp
  DEPENDS callingconv

  MODULE x86-fold-tables
  X86FoldTablesEmitter.cpp
  DEPENDS callingconv

  MODULE register-bank
  RegisterBankEmitter.cpp
  DEPENDS callingconv

  MODULE compress-inst-emitter
  RISCVCompressInstEmitter.cpp
  DEPENDS callingconv

  MODULE dfa-packetizer
  DFAPacketizerEmitter.cpp
  DEPENDS automata callingconv

  MODULE emitter
  CodeEmitterGen.cpp
  SubtargetFeatureInfo.cpp
  Types.cpp
  DEPENDS callingconv
  SHARED

  MODULE register-info
  RegisterInfoEmitter.cpp
  DEPENDS emitter intrinsic-impl

  MODULE subtarget
  PredicateExpander.cpp
  SubtargetEmitter.cpp
  DEPENDS callingconv
  SHARED

  MODULE asm-writer
  AsmWriterEmitter.cpp
  AsmWriterInst.cpp
  DEPENDS emitter intrinsic-impl

  MODULE asm-matcher
  AsmMatcherEmitter.cpp
  DEPENDS emitter

  MODULE disassembler
  DisassemblerEmitter.cpp
  FixedLenDecoderEmitter.cpp
  WebAssemblyDisassemblerEmitter.cpp
  X86DisassemblerTables.cpp
  X86ModRMFilters.cpp
  X86RecognizableInstr.cpp
  DEPENDS callingconv

  MODULE instr-docs
  CodeGenDAGPatterns.cpp
  InstrDocsEmitter.cpp
  DEPENDS callingconv
  SHARED

  MODULE fast-isel
  FastISelEmitter.cpp
  DEPENDS instr-docs

  MODULE instr-info
  CodeGenMapTable.cpp
  InstrInfoEmitter.cpp
  DEPENDS instr-docs intrinsic-impl subtarget

  MODULE global-isel
  GlobalISelEmitter.cpp
  DEPENDS emitter instr-docs

  MODULE dag-isel
  DAGISelEmitter.cpp
  DAGISelMatcher.cpp
  DAGISelMatcherEmitter.cpp
  DAGISelMatcherGen.cpp
  DAGISelMatcherOpt.cpp
  DEPENDS instr-docs

  MODULE global-isel-combiner
  GICombinerEmitter.cpp
  GlobalISel/CodeExpander.cpp
  GlobalISel/GIMatchDag.cpp
  GlobalISel/GIMatchDagEdge.cpp
  GlobalISel/GIMatchDagInstr.cpp
  GlobalISel/GIMatchDagOperands.cpp
  GlobalISel/GIMatchDagPredicate.cpp
  GlobalISel/GIMatchDagPredicateDependencyEdge.cpp
  GlobalISel/GIMatchTree.cpp
  DEPENDS callingconv
  ) # add_tablegen
set_target_properties(llvm-tblgen PROPERTIES FOLDER "Tablegenning")

if (LLVM_ENABLE_TABLEGEN_MODULARAIZED)
  add_library(LLVMTableGenGlobalISel ALIAS llvm-tblgen-global-isel-combiner)
endif()

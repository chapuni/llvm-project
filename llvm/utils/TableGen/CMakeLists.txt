set(LLVM_ENABLE_TABLEGEN_MODULARIZED ON)

add_tablegen(llvm-tblgen LLVM
  Attributes.cpp
  DirectiveEmitter.cpp
  OptEmitter.cpp
  OptParserEmitter.cpp
  OptRSTEmitter.cpp
  TableGen.cpp
  CTagsEmitter.cpp

  MODULE exegesis
  ExegesisEmitter.cpp

  MODULE intrinsic-enums
  CodeGenIntrinsics.cpp
  IntrinsicEnumsEmitter.cpp
  SDNodeProperties.cpp
  SHARED

  MODULE automata
  DFAEmitter.cpp
  SHARED

  MODULE searchable-tables
  SearchableTableEmitter.cpp
  DEPENDS intrinsic-enums

  MODULE intrinsic-impl
  EmitLongStrLiterals.cpp
  IntrinsicImplEmitter.cpp
  SHARED
  DEPENDS intrinsic-enums

  MODULE callingconv
  CallingConvEmitter.cpp
  CodeGenHwModes.cpp
  CodeGenInstruction.cpp
  CodeGenRegisters.cpp
  CodeGenSchedule.cpp
  CodeGenTarget.cpp
  InfoByHwMode.cpp
  SHARED
  DEPENDS intrinsic-impl

  MODULE pseudo-lowering
  PseudoLoweringEmitter.cpp
  DEPENDS callingconv

  MODULE x86-EVEX2VEX-tables
  X86EVEX2VEXTablesEmitter.cpp
  DEPENDS callingconv

  MODULE compress-inst-emitter
  RISCVCompressInstEmitter.cpp
  DEPENDS callingconv

  MODULE x86-fold-tables
  X86FoldTablesEmitter.cpp
  DEPENDS callingconv

  MODULE dfa-packetizer
  DFAPacketizerEmitter.cpp
  DEPENDS automata callingconv

  MODULE global-isel-combiner
  GICombinerEmitter.cpp
  $<TARGET_OBJECTS:obj.LLVMTableGenGlobalISel>

  MODULE instr-docs
  CodeGenDAGPatterns.cpp
  InstrDocsEmitter.cpp
  SHARED
  DEPENDS callingconv

  MODULE register-bank
  RegisterBankEmitter.cpp
  DEPENDS callingconv

  MODULE subtarget
  PredicateExpander.cpp
  SubtargetEmitter.cpp
  SHARED
  DEPENDS callingconv

  MODULE disassembler
  DisassemblerEmitter.cpp
  FixedLenDecoderEmitter.cpp # unused Action
  WebAssemblyDisassemblerEmitter.cpp
  X86DisassemblerTables.cpp
  X86ModRMFilters.cpp
  X86RecognizableInstr.cpp
  DEPENDS callingconv

  MODULE instr-info
  CodeGenMapTable.cpp
  InstrInfoEmitter.cpp
  DEPENDS instr-docs subtarget

  MODULE emitter
  CodeEmitterGen.cpp
  SubtargetFeatureInfo.cpp
  Types.cpp
  SHARED
  DEPENDS callingconv

  MODULE register-info
  RegisterInfoEmitter.cpp
  DEPENDS emitter

  MODULE asm-matcher
  AsmMatcherEmitter.cpp
  DEPENDS emitter

  MODULE asm-writer
  AsmWriterEmitter.cpp
  AsmWriterInst.cpp
  DEPENDS emitter

  MODULE fast-isel
  FastISelEmitter.cpp
  DEPENDS emitter instr-docs subtarget

  MODULE global-isel
  GlobalISelEmitter.cpp
  DEPENDS emitter instr-docs subtarget

  MODULE dag-isel
  DAGISelEmitter.cpp
  DAGISelMatcher.cpp
  DAGISelMatcherEmitter.cpp
  DAGISelMatcherGen.cpp
  DAGISelMatcherOpt.cpp

  DEPENDS emitter instr-docs
  ) # add_tablegen
set_target_properties(llvm-tblgen PROPERTIES FOLDER "Tablegenning")

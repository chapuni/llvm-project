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

  MODULE intrinsic-impl
  EmitLongStrLiterals.cpp
  IntrinsicImplEmitter.cpp
  DEPENDS intrinsic-enums
  SHARED

  MODULE searchable-tables
  SearchableTableEmitter.cpp
  DEPENDS intrinsic-enums

  MODULE automata
  DFAEmitter.cpp
  SHARED

  MODULE x86-EVEX2VEX-tables
  CodeGenHwModes.cpp
  CodeGenInstruction.cpp
  CodeGenRegisters.cpp
  CodeGenSchedule.cpp
  CodeGenTarget.cpp
  InfoByHwMode.cpp
  X86EVEX2VEXTablesEmitter.cpp
  DEPENDS intrinsic-enums
  SHARED

  MODULE callingconv
  CallingConvEmitter.cpp
  DEPENDS x86-EVEX2VEX-tables

  MODULE x86-fold-tables
  X86FoldTablesEmitter.cpp
  DEPENDS x86-EVEX2VEX-tables

  MODULE pseudo-lowering
  PseudoLoweringEmitter.cpp
  DEPENDS x86-EVEX2VEX-tables

  MODULE register-bank
  RegisterBankEmitter.cpp
  DEPENDS x86-EVEX2VEX-tables

  MODULE compress-inst-emitter
  RISCVCompressInstEmitter.cpp
  DEPENDS x86-EVEX2VEX-tables

  MODULE dfa-packetizer
  DFAPacketizerEmitter.cpp
  DEPENDS automata x86-EVEX2VEX-tables

  MODULE emitter
  CodeEmitterGen.cpp
  SubtargetFeatureInfo.cpp
  Types.cpp
  DEPENDS x86-EVEX2VEX-tables
  SHARED

  MODULE subtarget
  PredicateExpander.cpp
  SubtargetEmitter.cpp
  DEPENDS x86-EVEX2VEX-tables
  SHARED

  MODULE asm-writer
  AsmWriterEmitter.cpp
  AsmWriterInst.cpp
  DEPENDS emitter intrinsic-impl

  MODULE register-info
  RegisterInfoEmitter.cpp
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
  DEPENDS x86-EVEX2VEX-tables

  MODULE instr-docs
  CodeGenDAGPatterns.cpp
  InstrDocsEmitter.cpp
  DEPENDS x86-EVEX2VEX-tables
  SHARED

  MODULE fast-isel
  FastISelEmitter.cpp
  DEPENDS instr-docs

  MODULE instr-info
  CodeGenMapTable.cpp
  InstrInfoEmitter.cpp
  DEPENDS instr-docs intrinsic-impl subtarget

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
  DEPENDS x86-EVEX2VEX-tables
  SHARED

  MODULE global-isel
  GlobalISelEmitter.cpp
  DEPENDS emitter instr-docs
  ) # add_tablegen
set_target_properties(llvm-tblgen PROPERTIES FOLDER "Tablegenning")

add_library(LLVMTableGenGlobalISel ALIAS llvm-tblgen-global-isel-combiner)

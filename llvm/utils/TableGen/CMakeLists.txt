#add_subdirectory(GlobalISel)

add_llvm_library(LLVMTableGenCodeGen SHARED
  AsmWriterInst.cpp
  CodeGenDAGPatterns.cpp
  CodeGenHwModes.cpp
  CodeGenInstruction.cpp
  CodeGenRegisters.cpp
  CodeGenSchedule.cpp
  CodeGenTarget.cpp
  InfoByHwMode.cpp
  SDNodeProperties.cpp
  SubtargetFeatureInfo.cpp
  Types.cpp

  EmitLongStrLiterals.cpp

  PARTIAL_SOURCES_INTENDED

  LINK_LIBS
  LLVMTableGen
  LLVMSupport
  )

add_tablegen(llvm-tblgen LLVM
  Attributes.cpp
  CodeEmitterGen.cpp
  CodeGenMapTable.cpp
  DFAEmitter.cpp
  DFAPacketizerEmitter.cpp
  DirectiveEmitter.cpp
  DisassemblerEmitter.cpp
  ExegesisEmitter.cpp
  FastISelEmitter.cpp
  FixedLenDecoderEmitter.cpp
  GICombinerEmitter.cpp
  GlobalISelEmitter.cpp
  InstrInfoEmitter.cpp
  InstrDocsEmitter.cpp
  IntrinsicEmitter.cpp
  OptEmitter.cpp
  OptParserEmitter.cpp
  OptRSTEmitter.cpp
  PredicateExpander.cpp
  PseudoLoweringEmitter.cpp
  RISCVCompressInstEmitter.cpp
  RegisterBankEmitter.cpp
  RegisterInfoEmitter.cpp
  SearchableTableEmitter.cpp
  SubtargetEmitter.cpp
  TableGen.cpp
  X86DisassemblerTables.cpp
  X86EVEX2VEXTablesEmitter.cpp
  X86FoldTablesEmitter.cpp
  X86ModRMFilters.cpp
  X86RecognizableInstr.cpp
  WebAssemblyDisassemblerEmitter.cpp
  CTagsEmitter.cpp

  PARTIAL_SOURCES_INTENDED
  )
target_link_libraries(llvm-tblgen PRIVATE
  LLVMTableGenCodeGen
  LLVMTableGenGlobalISel
  )
set_target_properties(llvm-tblgen PROPERTIES FOLDER "Tablegenning")

add_custom_target(llvm-tblgen-all)

#add_dependencies(llvm-tblgen-all llvm-tblgen)
# XXX
add_dependencies(llvm-tblgen llvm-tblgen-all)

add_llvm_library(llvm-tblgen-asm-matcher MODULE
  AsmMatcherEmitter.cpp

  PARTIAL_SOURCES_INTENDED

  LINK_LIBS
  LLVMTableGenCodeGen
  LLVMTableGen
  LLVMSupport
  )
add_dependencies(llvm-tblgen-all llvm-tblgen-asm-matcher)

add_llvm_library(llvm-tblgen-asm-writer MODULE
  AsmWriterEmitter.cpp

  PARTIAL_SOURCES_INTENDED

  LINK_LIBS
  LLVMTableGenCodeGen
  LLVMTableGen
  LLVMSupport
  )
add_dependencies(llvm-tblgen-all llvm-tblgen-asm-writer)

add_llvm_library(llvm-tblgen-callingconv MODULE
  CallingConvEmitter.cpp

  PARTIAL_SOURCES_INTENDED

  LINK_LIBS
  LLVMTableGenCodeGen
  LLVMTableGen
  LLVMSupport
  )
add_dependencies(llvm-tblgen-all llvm-tblgen-callingconv)

add_llvm_library(llvm-tblgen-dag-isel MODULE
  DAGISelEmitter.cpp
  DAGISelMatcher.cpp
  DAGISelMatcherEmitter.cpp
  DAGISelMatcherGen.cpp
  DAGISelMatcherOpt.cpp

  PARTIAL_SOURCES_INTENDED

  LINK_LIBS
  LLVMTableGenCodeGen
  LLVMTableGen
  LLVMSupport
  )
add_dependencies(llvm-tblgen-all llvm-tblgen-dag-isel)

llvm_check_source_file_list()

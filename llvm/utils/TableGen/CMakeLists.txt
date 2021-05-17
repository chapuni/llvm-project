#add_subdirectory(GlobalISel)

add_llvm_library(LLVMTableGenCodeGen SHARED
  AsmWriterInst.cpp
  CodeGenDAGPatterns.cpp
  CodeGenHwModes.cpp
  CodeGenInstruction.cpp
  CodeGenMapTable.cpp
  CodeGenRegisters.cpp
  CodeGenSchedule.cpp
  CodeGenTarget.cpp
  InfoByHwMode.cpp
  PredicateExpander.cpp
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
  DFAEmitter.cpp
  DFAPacketizerEmitter.cpp
  DirectiveEmitter.cpp
  DisassemblerEmitter.cpp
  FixedLenDecoderEmitter.cpp
  InstrDocsEmitter.cpp
  IntrinsicEmitter.cpp
  OptEmitter.cpp
  OptParserEmitter.cpp
  OptRSTEmitter.cpp
  PseudoLoweringEmitter.cpp
  RISCVCompressInstEmitter.cpp
  SearchableTableEmitter.cpp
  SubtargetEmitter.cpp
  TableGen.cpp
  X86DisassemblerTables.cpp
  X86FoldTablesEmitter.cpp
  X86ModRMFilters.cpp
  X86RecognizableInstr.cpp
  WebAssemblyDisassemblerEmitter.cpp
  CTagsEmitter.cpp

  PARTIAL_SOURCES_INTENDED
  )
target_link_libraries(llvm-tblgen PRIVATE
  LLVMTableGenCodeGen
  LLVMTableGen
  LLVMSupport
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

add_llvm_library(llvm-tblgen-x86-EVEX2VEX-tables MODULE
  X86EVEX2VEXTablesEmitter.cpp

  PARTIAL_SOURCES_INTENDED

  LINK_LIBS
  LLVMTableGenCodeGen
  LLVMTableGen
  LLVMSupport
  )
add_dependencies(llvm-tblgen-all llvm-tblgen-x86-EVEX2VEX-tables)

add_llvm_library(llvm-tblgen-exegesis MODULE
  ExegesisEmitter.cpp

  PARTIAL_SOURCES_INTENDED

  LINK_LIBS
  LLVMTableGen
  LLVMSupport
  )
add_dependencies(llvm-tblgen-all llvm-tblgen-exegesis)

add_llvm_library(llvm-tblgen-fast-isel MODULE
  FastISelEmitter.cpp

  PARTIAL_SOURCES_INTENDED

  LINK_LIBS
  LLVMTableGenCodeGen
  LLVMTableGen
  LLVMSupport
  )
add_dependencies(llvm-tblgen-all llvm-tblgen-fast-isel)

add_llvm_library(llvm-tblgen-global-isel MODULE
  GlobalISelEmitter.cpp

  PARTIAL_SOURCES_INTENDED

  LINK_LIBS
  LLVMTableGenCodeGen
  LLVMTableGen
  LLVMSupport
  )
add_dependencies(llvm-tblgen-all llvm-tblgen-global-isel)

add_llvm_library(llvm-tblgen-global-isel-combiner MODULE
  GICombinerEmitter.cpp
  $<TARGET_OBJECTS:obj.LLVMTableGenGlobalISel>

  PARTIAL_SOURCES_INTENDED

  LINK_LIBS
  LLVMTableGenCodeGen
  LLVMTableGen
  LLVMSupport
  )
add_dependencies(llvm-tblgen-all llvm-tblgen-global-isel-combiner)

add_llvm_library(llvm-tblgen-instr-info MODULE
  InstrInfoEmitter.cpp

  PARTIAL_SOURCES_INTENDED

  LINK_LIBS
  LLVMTableGenCodeGen
  LLVMTableGen
  LLVMSupport
  )
add_dependencies(llvm-tblgen-all llvm-tblgen-instr-info)

add_llvm_library(llvm-tblgen-register-bank MODULE
  RegisterBankEmitter.cpp

  PARTIAL_SOURCES_INTENDED

  LINK_LIBS
  LLVMTableGenCodeGen
  LLVMTableGen
  LLVMSupport
  )
add_dependencies(llvm-tblgen-all llvm-tblgen-register-bank)

add_llvm_library(llvm-tblgen-register-info MODULE
  RegisterInfoEmitter.cpp

  PARTIAL_SOURCES_INTENDED

  LINK_LIBS
  LLVMTableGenCodeGen
  LLVMTableGen
  LLVMSupport
  )
add_dependencies(llvm-tblgen-all llvm-tblgen-register-info)

llvm_check_source_file_list()

add_llvm_library(LLVM_all_modules STATIC BUILDTREE_ONLY PARTIAL_SOURCES_INTENDED
  LLVM_Utils.cpp
  LLVM_Config_Config.cpp
  std_config.cpp
  _Builtin_stddef_max_align_t.cpp
  std.cpp
  LLVM_C.cpp
  LLVM_Config_ABI_Breaking.cpp
  LLVM_Support_TargetRegistry.cpp
  LLVM_MC_TableGen.cpp
  LLVM_BinaryFormat.cpp
  LLVM_TableGen.cpp
  LLVM_Pass.cpp
  LLVM_IR.cpp
  LLVM_Bitstream.cpp
  LLVM_MC.cpp
  LLVM_Object.cpp
  LLVM_intrinsic_gen.cpp
  )

add_llvm_library(LLVM_modules_stub STATIC BUILDTREE_ONLY PARTIAL_SOURCES_INTENDED
  stub.cpp
  )

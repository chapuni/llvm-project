set(LLVM_TARGET_DEFINITIONS Attributes.td)
tablegen(LLVM Attributes.inc -gen-attrs)

set(LLVM_TARGET_DEFINITIONS Intrinsics.td)
tablegen(LLVM IntrinsicImpl.inc -gen-intrinsic-impl)
tablegen(LLVM IntrinsicEnums.inc -gen-intrinsic-enums)
tablegen(LLVM IntrinsicsAArch64.h -gen-intrinsic-enums -intrinsic-prefix=aarch64)
tablegen(LLVM IntrinsicsAMDGPU.h -gen-intrinsic-enums -intrinsic-prefix=amdgcn)
tablegen(LLVM IntrinsicsARM.h -gen-intrinsic-enums -intrinsic-prefix=arm)
tablegen(LLVM IntrinsicsBPF.h -gen-intrinsic-enums -intrinsic-prefix=bpf)
tablegen(LLVM IntrinsicsHexagon.h -gen-intrinsic-enums -intrinsic-prefix=hexagon)
tablegen(LLVM IntrinsicsMips.h -gen-intrinsic-enums -intrinsic-prefix=mips)
tablegen(LLVM IntrinsicsNVPTX.h -gen-intrinsic-enums -intrinsic-prefix=nvvm)
tablegen(LLVM IntrinsicsPowerPC.h -gen-intrinsic-enums -intrinsic-prefix=ppc)
tablegen(LLVM IntrinsicsR600.h -gen-intrinsic-enums -intrinsic-prefix=r600)
tablegen(LLVM IntrinsicsRISCV.h -gen-intrinsic-enums -intrinsic-prefix=riscv)
tablegen(LLVM IntrinsicsS390.h -gen-intrinsic-enums -intrinsic-prefix=s390)
tablegen(LLVM IntrinsicsWebAssembly.h -gen-intrinsic-enums -intrinsic-prefix=wasm)
tablegen(LLVM IntrinsicsX86.h -gen-intrinsic-enums -intrinsic-prefix=x86)
tablegen(LLVM IntrinsicsXCore.h -gen-intrinsic-enums -intrinsic-prefix=xcore)
tablegen(LLVM IntrinsicsVE.h -gen-intrinsic-enums -intrinsic-prefix=ve)

#add_public_tablegen_target(intrinsics_gen)

add_library(intrinsics_gen INTERFACE
  Attributes.inc
  IntrinsicImpl.inc
  IntrinsicEnums.inc
  IntrinsicsAArch64.h
  IntrinsicsAMDGPU.h
  IntrinsicsARM.h
  IntrinsicsBPF.h
  IntrinsicsHexagon.h
  IntrinsicsMips.h
  IntrinsicsNVPTX.h
  IntrinsicsPowerPC.h
  IntrinsicsR600.h
  IntrinsicsRISCV.h
  IntrinsicsS390.h
  IntrinsicsWebAssembly.h
  IntrinsicsX86.h
  IntrinsicsXCore.h
  IntrinsicsVE.h
  )

set_target_properties(intrinsics_gen
  PROPERTIES HEADER_FILE_ONLY ON
  )

# export(TARGETS intrinsics_gen
#   FILE xxx.cmake
#   )

# install(EXPORT xxx.cmake DESTINATION XXX)

install(TARGETS intrinsics_gen
  EXPORT LLVMExports
  DESTINATION bin
  COMPONENT intrinsics_gen
  )

set_property(GLOBAL APPEND PROPERTY LLVM_EXPORTS intrinsics_gen)

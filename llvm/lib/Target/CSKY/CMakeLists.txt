add_llvm_component_group(CSKY)

set(LLVM_TARGET_DEFINITIONS CSKY.td)

tablegen(LLVM CSKYGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM CSKYGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM CSKYGenMCCodeEmitter.inc -gen-emitter)

add_public_tablegen_target(CSKYCommonTableGen)

add_llvm_target(CSKYCodeGen
  CSKYTargetMachine.cpp

  LINK_COMPONENTS

  ADD_TO_COMPONENT
  CSKY
  )

set(xxx
  Core
  CodeGen
  CSKYInfo
  Support
  Target
  )

add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)

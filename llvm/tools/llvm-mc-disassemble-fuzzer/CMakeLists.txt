set(LLVM_LINK_COMPONENTS
  )

set(xxx
    AllTargetsDescs
    AllTargetsDisassemblers
    AllTargetsInfos
    MC
    MCDisassembler
    MCParser
    Support
)
add_llvm_fuzzer(llvm-mc-disassemble-fuzzer
  llvm-mc-disassemble-fuzzer.cpp
  )

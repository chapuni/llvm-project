set(LLVM_LINK_COMPONENTS
  )

set(xxx
  Core Demangle Object Remarks Support)

add_llvm_tool(llvm-opt-report
  OptReport.cpp
  )


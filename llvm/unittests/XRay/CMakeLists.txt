set(LLVM_LINK_COMPONENTS
  )

set(xxx
  Support
  XRay
  LLVMTestingSupport
  )

add_llvm_unittest(XRayTests
  FDRBlockIndexerTest.cpp
  FDRBlockVerifierTest.cpp
  FDRProducerConsumerTest.cpp
  FDRRecordPrinterTest.cpp
  FDRRecordsTest.cpp
  FDRTraceWriterTest.cpp
  GraphTest.cpp
  ProfileTest.cpp
  )

add_dependencies(XRayTests intrinsics_gen)

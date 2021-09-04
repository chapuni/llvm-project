set(LLVM_LINK_COMPONENTS
  Support
  XRay
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

target_link_libraries(XRayTests PRIVATE LLVMTestingSupport)

#!/usr/bin/env python

mods = {
    "2MV1550QFQX2B" : [
        "LLVM_Analysis",
        "LLVM_AsmParser",
        "LLVM_Backend",
        "LLVM_Backend_Target",
        "LLVM_BinaryFormat",
        "LLVM_Bitcode",
        "LLVM_Bitstream",
        "LLVM_DebugInfo",
        "LLVM_DebugInfo_CodeView",
        "LLVM_DebugInfo_DWARF",
        "LLVM_DebugInfo_MSF",
        "LLVM_DebugInfo_PDB",
        "LLVM_DWARFLinker",
        "LLVM_ExecutionEngine",
        "LLVM_FileCheck",
        "LLVM_intrinsic_gen",
        "LLVM_IR",
        "LLVM_IRReader",
        "LLVM_LineEditor",
        "LLVM_LTO",
        "LLVM_MC",
        "LLVM_MC_TableGen",
        "LLVM_Object",
        "LLVM_Option",
        "LLVM_OrcSupport",
        "LLVM_Pass",
        "LLVM_ProfileData",
        "LLVM_Support_TargetRegistry",
        "LLVM_TableGen",
        "LLVM_Transforms",
        "LLVM_Utils",
        "LLVM_WindowsManifest",
    ],
    "2UDXE123T4NS" : [
        "LLVM_C",
    ],
    "2ZZPSZBIF2XCH" : [
        "LLVM_Config_ABI_Breaking",
        "LLVM_Config_Config",
    ],
    "3SAY5OFB9VLDU" : [
        "Clang_Analysis",
        "Clang_AST",
        "Clang_ASTMatchers",
        "Clang_Basic",
        "Clang_CodeGen",
        "Clang_Diagnostics",
        "Clang_Driver",
        "Clang_Edit",
        "Clang_Format",
        "Clang_Frontend",
        "Clang_FrontendTool",
        "Clang_Index",
        "Clang_Lex",
        "Clang_Parse",
        "Clang_Rewrite",
        "Clang_RewriteFrontend",
        "Clang_Sema",
        "Clang_Serialization",
        "Clang_StaticAnalyzer_Checkers",
        "Clang_StaticAnalyzer_Core",
        "Clang_StaticAnalyzer_Frontend",
        "Clang_Testing",
        "Clang_Tooling",
        "Clang_ToolingCore",
        "Clang_ToolingInclusions",
    ],
    "6U4XRCQILCF1" : [
        "std",
        "std_config",
    ],
    "157N363DC7KLC" : [
        "_Builtin_intrinsics",
        "_Builtin_stddef_max_align_t",
    ],

    "X08R0ZBQONMG" : [
        "Clang_C",
    ],
}

for (h,ms) in mods.items():
    for m in ms:
        cfn = "stub_%s.cpp" % m
        mn = "mod_%s" % m
        with open("xxx/%s" % cfn, "w") as f:
            f.write("#pragma clang module import %s\n" % m)
        print("llvm_add_library(%s %s)" % (mn, cfn))
        print("set_target_properties(%s PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})" % (mn))
        print("set_source_files_properties(%s PROPERTIES OBJECT_OUTPUTS ${CMAKE_BINARY_DIR}/module.cache/%s/%s-%s.pcm)" % (cfn, "A27QS4X7KY8D", m, h))
        print("add_dependencies(%s anchor_all)" % mn)

#EOF

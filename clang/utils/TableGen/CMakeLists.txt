set(LLVM_ENABLE_TABLEGEN_MODULARIZED OFF)

add_tablegen(clang-tblgen CLANG
  ASTTableGen.cpp
  ClangASTNodesEmitter.cpp
  ClangASTPropertiesEmitter.cpp
  ClangCommentCommandInfoEmitter.cpp
  ClangCommentHTMLNamedCharacterReferenceEmitter.cpp
  ClangCommentHTMLTagsEmitter.cpp
  ClangDataCollectorsEmitter.cpp
  ClangDiagnosticsEmitter.cpp
  ClangOpcodesEmitter.cpp
  ClangOpenCLBuiltinEmitter.cpp
  ClangOptionDocEmitter.cpp
  ClangSACheckersEmitter.cpp
  ClangSyntaxEmitter.cpp
  ClangTypeNodesEmitter.cpp
  MveEmitter.cpp
  NeonEmitter.cpp
  SveEmitter.cpp
  TableGen.cpp

  MODULE clang-attr-classes
  ClangAttrClasses.cpp
  ClangAttrEmitter.cpp

  MODULE clang-attr-parser-string-switches
  ClangAttrParserStringSwitches.cpp
  DEPENDS clang-attr-classes

  MODULE clang-attr-subject-match-rules-parser-string-switches
  ClangAttrSubjectMatchRulesParserStringSwitches.cpp
  DEPENDS clang-attr-classes

  MODULE clang-attr-impl
  ClangAttrImpl.cpp
  DEPENDS clang-attr-classes

  MODULE clang-attr-list
  ClangAttrList.cpp
  DEPENDS clang-attr-classes

  MODULE clang-attr-subject-match-rule-list
  ClangAttrSubjectMatchRuleList.cpp
  DEPENDS clang-attr-classes

  MODULE clang-attr-pch-read
  ClangAttrPCHRead.cpp
  DEPENDS clang-attr-classes

  MODULE clang-attr-pch-write
  ClangAttrPCHWrite.cpp
  DEPENDS clang-attr-classes

  MODULE clang-attr-has-attribute-impl
  ClangAttrHasAttributeImpl.cpp
  DEPENDS clang-attr-classes

  MODULE clang-attr-spelling-index
  ClangAttrSpellingListIndex.cpp
  DEPENDS clang-attr-classes

  MODULE clang-attr-ast-visitor
  ClangAttrASTVisitor.cpp
  DEPENDS clang-attr-classes

  MODULE clang-attr-template-instantiate
  ClangAttrTemplateInstantiate.cpp
  DEPENDS clang-attr-classes

  MODULE clang-attr-parsed-attr-list
  ClangAttrParsedAttrList.cpp
  DEPENDS clang-attr-classes

  MODULE clang-attr-parsed-attr-impl
  ClangAttrParsedAttrImpl.cpp
  DEPENDS clang-attr-classes

  MODULE clang-attr-parsed-attr-kinds
  ClangAttrParsedAttrKinds.cpp
  DEPENDS clang-attr-classes

  MODULE clang-attr-text-node-dump
  ClangAttrTextNodeDump.cpp
  DEPENDS clang-attr-classes

  MODULE clang-attr-node-traverse
  ClangAttrNodeTraverse.cpp
  DEPENDS clang-attr-classes

  MODULE clang-diags-defs
  ClangDiagsDefs.cpp
  DEPENDS clang-attr-classes

  MODULE clang-diag-groups
  ClangDiagGroups.cpp
  DEPENDS clang-attr-classes

  MODULE clang-diags-index-name
  ClangDiagsIndexName.cpp
  DEPENDS clang-attr-classes

  MODULE clang-comment-nodes
  ClangCommentNodes.cpp
  DEPENDS clang-attr-classes

  MODULE clang-decl-nodes
  ClangDeclNodes.cpp
  DEPENDS clang-attr-classes

  MODULE clang-stmt-nodes
  ClangStmtNodes.cpp
  DEPENDS clang-attr-classes

  MODULE clang-type-nodes
  ClangTypeNodes.cpp
  DEPENDS clang-attr-classes

  MODULE clang-type-reader
  ClangTypeReader.cpp
  DEPENDS clang-attr-classes

  MODULE clang-type-writer
  ClangTypeWriter.cpp
  DEPENDS clang-attr-classes

  MODULE clang-basic-reader
  ClangBasicReader.cpp
  DEPENDS clang-attr-classes

  MODULE clang-basic-writer
  ClangBasicWriter.cpp
  DEPENDS clang-attr-classes

  MODULE clang-opcodes
  ClangOpcodes.cpp
  DEPENDS clang-attr-classes

  MODULE clang-sa-checkers
  ClangSACheckers.cpp
  DEPENDS clang-attr-classes

  MODULE clang-comment-html-tags-properties
  ClangCommentHTMLTagsProperties.cpp
  DEPENDS clang-attr-classes

  MODULE clang-comment-html-named-character-references
  ClangCommentHTMLNamedCharacterReferences.cpp
  DEPENDS clang-attr-classes

  MODULE clang-comment-html-tags
  ClangCommentHTMLTags.cpp
  DEPENDS clang-attr-classes

  MODULE clang-comment-command-info
  ClangCommentCommandInfo.cpp
  DEPENDS clang-attr-classes

  MODULE clang-comment-command-list
  ClangCommentCommandList.cpp
  DEPENDS clang-attr-classes

  MODULE clang-opencl-builtins
  ClangOpenCLBuiltins.cpp
  DEPENDS clang-attr-classes

  MODULE clang-syntax-node-list
  ClangSyntaxNodeList.cpp
  DEPENDS clang-attr-classes

  MODULE clang-syntax-node-classes
  ClangSyntaxNodeClasses.cpp
  DEPENDS clang-attr-classes

  MODULE arm-neon
  ArmNeon.cpp
  DEPENDS clang-attr-classes

  MODULE arm-fp16
  ArmFP16.cpp
  DEPENDS clang-attr-classes

  MODULE arm-bf16
  ArmBF16.cpp
  DEPENDS clang-attr-classes

  MODULE arm-neon-sema
  ArmNeonSema.cpp
  DEPENDS clang-attr-classes

  MODULE arm-neon-test
  ArmNeonTest.cpp
  DEPENDS clang-attr-classes

  MODULE arm-mve-header
  ArmMveHeader.cpp
  DEPENDS clang-attr-classes

  MODULE arm-mve-builtin-def
  ArmMveBuiltinDef.cpp
  DEPENDS clang-attr-classes

  MODULE arm-mve-builtin-sema
  ArmMveBuiltinSema.cpp
  DEPENDS clang-attr-classes

  MODULE arm-mve-builtin-codegen
  ArmMveBuiltinCG.cpp
  DEPENDS clang-attr-classes

  MODULE arm-mve-builtin-aliases
  ArmMveBuiltinAliases.cpp
  DEPENDS clang-attr-classes

  MODULE arm-sve-header
  ArmSveHeader.cpp
  DEPENDS clang-attr-classes

  MODULE arm-sve-builtins
  ArmSveBuiltins.cpp
  DEPENDS clang-attr-classes

  MODULE arm-sve-builtin-codegen
  ArmSveBuiltinCG.cpp
  DEPENDS clang-attr-classes

  MODULE arm-sve-typeflags
  ArmSveTypeFlags.cpp
  DEPENDS clang-attr-classes

  MODULE arm-sve-sema-rangechecks
  ArmSveRangeChecks.cpp
  DEPENDS clang-attr-classes

  MODULE arm-cde-header
  ArmCdeHeader.cpp
  DEPENDS clang-attr-classes

  MODULE arm-cde-builtin-def
  ArmCdeBuiltinDef.cpp
  DEPENDS clang-attr-classes

  MODULE arm-cde-builtin-sema
  ArmCdeBuiltinSema.cpp
  DEPENDS clang-attr-classes

  MODULE arm-cde-builtin-codegen
  ArmCdeBuiltinCG.cpp
  DEPENDS clang-attr-classes

  MODULE arm-cde-builtin-aliases
  ArmCdeBuiltinAliases.cpp
  DEPENDS clang-attr-classes

  MODULE attr-docs
  AttrDocs.cpp
  DEPENDS clang-attr-classes

  MODULE diag-docs
  DiagDocs.cpp
  DEPENDS clang-attr-classes

  MODULE opt-docs
  OptDocs.cpp
  DEPENDS clang-attr-classes

  MODULE clang-data-collectors
  DataCollectors.cpp
  DEPENDS clang-attr-classes

  MODULE clang-test-pragma-attribute-supported-attributes
  TestPragmaAttributeSupportedAttributes.cpp
  DEPENDS clang-attr-classes
  )
set_target_properties(clang-tblgen PROPERTIES FOLDER "Clang tablegenning")

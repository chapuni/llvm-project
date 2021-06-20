add_tablegen(clang-tblgen CLANG
  TableGen.cpp

  MODULE clang-data-collectors
  ClangDataCollectorsEmitter.cpp

  MODULE clang-comment-command-info
  ClangCommentCommandInfoEmitter.cpp

  MODULE clang-comment-html-tags-properties
  ClangCommentHTMLTagsProperties.cpp

  MODULE clang-comment-command-list
  ClangCommentCommandList.cpp

  MODULE clang-syntax-node-list
  ClangSyntaxEmitter.cpp
  SHARED

  MODULE clang-syntax-node-classes
  ClangSyntaxNodeClasses.cpp
  DEPENDS clang-syntax-node-list

  MODULE clang-opencl-builtins
  ClangOpenCLBuiltinEmitter.cpp

  MODULE clang-comment-html-named-character-references
  ClangCommentHTMLNamedCharacterReferenceEmitter.cpp

  MODULE arm-sve-header
  ArmSveHeader.cpp
  SveEmitter.cpp
  SHARED

  MODULE arm-sve-sema-rangechecks
  ArmSveRangeChecks.cpp
  DEPENDS arm-sve-header

  MODULE arm-sve-typeflags
  ArmSveTypeFlags.cpp
  DEPENDS arm-sve-header

  MODULE arm-sve-builtin-codegen
  ArmSveBuiltinCG.cpp
  DEPENDS arm-sve-header

  MODULE arm-sve-builtins
  ArmSveBuiltins.cpp
  DEPENDS arm-sve-header

  MODULE clang-comment-html-tags
  ClangCommentHTMLTagsEmitter.cpp

  MODULE clang-sa-checkers
  ClangSACheckersEmitter.cpp

  MODULE arm-cde-builtin-sema
  ArmCdeBuiltinSema.cpp
  MveEmitter.cpp
  SHARED

  MODULE arm-mve-builtin-codegen
  ArmMveBuiltinCG.cpp
  DEPENDS arm-cde-builtin-sema

  MODULE arm-mve-builtin-aliases
  ArmMveBuiltinAliases.cpp
  DEPENDS arm-cde-builtin-sema

  MODULE arm-cde-builtin-codegen
  ArmCdeBuiltinCG.cpp
  DEPENDS arm-cde-builtin-sema

  MODULE arm-mve-header
  ArmMveHeader.cpp
  DEPENDS arm-cde-builtin-sema

  MODULE arm-cde-header
  ArmCdeHeader.cpp
  DEPENDS arm-cde-builtin-sema

  MODULE arm-cde-builtin-aliases
  ArmCdeBuiltinAliases.cpp
  DEPENDS arm-cde-builtin-sema

  MODULE arm-cde-builtin-def
  ArmCdeBuiltinDef.cpp
  DEPENDS arm-cde-builtin-sema

  MODULE arm-mve-builtin-sema
  ArmMveBuiltinSema.cpp
  DEPENDS arm-cde-builtin-sema

  MODULE arm-mve-builtin-def
  ArmMveBuiltinDef.cpp
  DEPENDS arm-cde-builtin-sema

  MODULE clang-opcodes
  ClangOpcodesEmitter.cpp

  MODULE clang-diags-index-name
  ClangDiagnosticsEmitter.cpp
  ClangDiagsIndexName.cpp
  SHARED

  MODULE diag-docs
  DiagDocs.cpp
  DEPENDS clang-diags-index-name

  MODULE clang-diag-groups
  ClangDiagGroups.cpp
  DEPENDS clang-diags-index-name

  MODULE clang-diags-defs
  ClangDiagsDefs.cpp
  DEPENDS clang-diags-index-name

  MODULE clang-type-nodes
  ASTTableGen.cpp
  ClangTypeNodesEmitter.cpp
  SHARED

  MODULE clang-type-writer
  ClangASTPropertiesEmitter.cpp
  ClangTypeWriter.cpp
  DEPENDS clang-type-nodes
  SHARED

  MODULE clang-type-reader
  ClangTypeReader.cpp
  DEPENDS clang-type-writer

  MODULE clang-basic-reader
  ClangBasicReader.cpp
  DEPENDS clang-type-writer

  MODULE clang-basic-writer
  ClangBasicWriter.cpp
  DEPENDS clang-type-writer

  MODULE arm-bf16
  ArmBF16.cpp
  NeonEmitter.cpp
  SHARED

  MODULE arm-neon-test
  ArmNeonTest.cpp
  DEPENDS arm-bf16

  MODULE arm-neon-sema
  ArmNeonSema.cpp
  DEPENDS arm-bf16

  MODULE arm-neon
  ArmNeon.cpp
  DEPENDS arm-bf16

  MODULE arm-fp16
  ArmFP16.cpp
  DEPENDS arm-bf16

  MODULE clang-comment-nodes
  ClangASTNodesEmitter.cpp
  ClangCommentNodes.cpp
  SHARED

  MODULE clang-stmt-nodes
  ClangStmtNodes.cpp
  DEPENDS clang-comment-nodes

  MODULE clang-decl-nodes
  ClangDeclNodes.cpp
  DEPENDS clang-comment-nodes

  MODULE opt-docs
  ClangOptionDocEmitter.cpp

  MODULE clang-test-pragma-attribute-supported-attributes
  ClangAttrEmitter.cpp
  TestPragmaAttributeSupportedAttributes.cpp
  SHARED

  MODULE clang-attr-parsed-attr-kinds
  ClangAttrParsedAttrKinds.cpp
  DEPENDS clang-test-pragma-attribute-supported-attributes

  MODULE clang-attr-subject-match-rule-list
  ClangAttrSubjectMatchRuleList.cpp
  DEPENDS clang-test-pragma-attribute-supported-attributes

  MODULE clang-attr-subject-match-rules-parser-string-switches
  ClangAttrSubjectMatchRulesParserStringSwitches.cpp
  DEPENDS clang-test-pragma-attribute-supported-attributes

  MODULE clang-attr-node-traverse
  ClangAttrNodeTraverse.cpp
  DEPENDS clang-test-pragma-attribute-supported-attributes

  MODULE clang-attr-list
  ClangAttrList.cpp
  DEPENDS clang-test-pragma-attribute-supported-attributes

  MODULE clang-attr-ast-visitor
  ClangAttrASTVisitor.cpp
  DEPENDS clang-test-pragma-attribute-supported-attributes

  MODULE attr-docs
  AttrDocs.cpp
  DEPENDS clang-test-pragma-attribute-supported-attributes

  MODULE clang-attr-template-instantiate
  ClangAttrTemplateInstantiate.cpp
  DEPENDS clang-test-pragma-attribute-supported-attributes

  MODULE clang-attr-classes
  ClangAttrClasses.cpp
  DEPENDS clang-test-pragma-attribute-supported-attributes

  MODULE clang-attr-parsed-attr-list
  ClangAttrParsedAttrList.cpp
  DEPENDS clang-test-pragma-attribute-supported-attributes

  MODULE clang-attr-text-node-dump
  ClangAttrTextNodeDump.cpp
  DEPENDS clang-test-pragma-attribute-supported-attributes

  MODULE clang-attr-pch-read
  ClangAttrPCHRead.cpp
  DEPENDS clang-test-pragma-attribute-supported-attributes

  MODULE clang-attr-pch-write
  ClangAttrPCHWrite.cpp
  DEPENDS clang-test-pragma-attribute-supported-attributes

  MODULE clang-attr-spelling-index
  ClangAttrSpellingListIndex.cpp
  DEPENDS clang-test-pragma-attribute-supported-attributes

  MODULE clang-attr-parsed-attr-impl
  ClangAttrParsedAttrImpl.cpp
  DEPENDS clang-test-pragma-attribute-supported-attributes

  MODULE clang-attr-parser-string-switches
  ClangAttrParserStringSwitches.cpp
  DEPENDS clang-test-pragma-attribute-supported-attributes

  MODULE clang-attr-impl
  ClangAttrImpl.cpp
  DEPENDS clang-test-pragma-attribute-supported-attributes

  MODULE clang-attr-has-attribute-impl
  ClangAttrHasAttributeImpl.cpp
  DEPENDS clang-test-pragma-attribute-supported-attributes
  )
set_target_properties(clang-tblgen PROPERTIES FOLDER "Clang tablegenning")

set(LLVM_ENABLE_TABLEGEN_MODULARIZED ON)

add_tablegen(clang-tblgen CLANG
  TableGen.cpp

  MODULE clang-data-collectors
  ClangDataCollectorsEmitter.cpp

  MODULE clang-syntax-node-list
  ClangSyntaxEmitter.cpp
  SHARED

  MODULE clang-syntax-node-classes
  ClangSyntaxNodeClasses.cpp
  DEPENDS clang-syntax-node-list

  MODULE opt-docs
  ClangOptionDocEmitter.cpp
  OptDocs.cpp

  MODULE clang-opcodes
  ClangOpcodesEmitter.cpp

  MODULE clang-opencl-builtins
  ClangOpenCLBuiltinEmitter.cpp

  MODULE clang-sa-checkers
  ClangSACheckersEmitter.cpp

  MODULE clang-comment-html-named-character-references
  ClangCommentHTMLNamedCharacterReferenceEmitter.cpp

  MODULE clang-comment-html-tags
  ClangCommentHTMLTagsEmitter.cpp
  SHARED

  MODULE clang-comment-html-tags-properties
  ClangCommentHTMLTagsProperties.cpp
  DEPENDS clang-comment-html-tags

  MODULE clang-type-nodes
  ASTTableGen.cpp
  ClangTypeNodesEmitter.cpp
  SHARED

  MODULE clang-type-writer
  ClangASTPropertiesEmitter.cpp
  ClangTypeWriter.cpp
  DEPENDS clang-type-nodes
  SHARED

  MODULE clang-basic-reader
  ClangBasicReader.cpp
  DEPENDS clang-type-writer

  MODULE clang-type-reader
  ClangTypeReader.cpp
  DEPENDS clang-type-writer

  MODULE clang-basic-writer
  ClangBasicWriter.cpp
  DEPENDS clang-type-writer

  MODULE clang-comment-command-list
  ClangCommentCommandInfoEmitter.cpp
  ClangCommentCommandList.cpp
  SHARED

  MODULE clang-comment-command-info
  ClangCommentCommandInfo.cpp
  DEPENDS clang-comment-command-list

  MODULE clang-comment-nodes
  ClangASTNodesEmitter.cpp
  ClangCommentNodes.cpp
  SHARED

  MODULE clang-decl-nodes
  ClangDeclNodes.cpp
  DEPENDS clang-comment-nodes

  MODULE clang-stmt-nodes
  ClangStmtNodes.cpp
  DEPENDS clang-comment-nodes

  MODULE diag-docs
  ClangDiagnosticsEmitter.cpp
  DiagDocs.cpp
  SHARED

  MODULE clang-diag-groups
  ClangDiagGroups.cpp
  DEPENDS diag-docs

  MODULE clang-diags-index-name
  ClangDiagsIndexName.cpp
  DEPENDS diag-docs

  MODULE clang-diags-defs
  ClangDiagsDefs.cpp
  DEPENDS diag-docs

  MODULE arm-sve-sema-rangechecks
  ArmSveRangeChecks.cpp
  SveEmitter.cpp
  SHARED

  MODULE arm-sve-typeflags
  ArmSveTypeFlags.cpp
  DEPENDS arm-sve-sema-rangechecks

  MODULE arm-sve-builtin-codegen
  ArmSveBuiltinCG.cpp
  DEPENDS arm-sve-sema-rangechecks

  MODULE arm-sve-header
  ArmSveHeader.cpp
  DEPENDS arm-sve-sema-rangechecks

  MODULE arm-sve-builtins
  ArmSveBuiltins.cpp
  DEPENDS arm-sve-sema-rangechecks

  MODULE clang-attr-has-attribute-impl
  ClangAttrEmitter.cpp
  ClangAttrHasAttributeImpl.cpp
  SHARED

  MODULE clang-attr-pch-read
  ClangAttrPCHRead.cpp
  DEPENDS clang-attr-has-attribute-impl

  MODULE clang-attr-node-traverse
  ClangAttrNodeTraverse.cpp
  DEPENDS clang-attr-has-attribute-impl

  MODULE clang-attr-subject-match-rules-parser-string-switches
  ClangAttrSubjectMatchRulesParserStringSwitches.cpp
  DEPENDS clang-attr-has-attribute-impl

  MODULE clang-test-pragma-attribute-supported-attributes
  TestPragmaAttributeSupportedAttributes.cpp
  DEPENDS clang-attr-has-attribute-impl

  MODULE clang-attr-pch-write
  ClangAttrPCHWrite.cpp
  DEPENDS clang-attr-has-attribute-impl

  MODULE clang-attr-classes
  ClangAttrClasses.cpp
  DEPENDS clang-attr-has-attribute-impl

  MODULE clang-attr-list
  ClangAttrList.cpp
  DEPENDS clang-attr-has-attribute-impl

  MODULE clang-attr-parsed-attr-impl
  ClangAttrParsedAttrImpl.cpp
  DEPENDS clang-attr-has-attribute-impl

  MODULE clang-attr-impl
  ClangAttrImpl.cpp
  DEPENDS clang-attr-has-attribute-impl

  MODULE clang-attr-spelling-index
  ClangAttrSpellingListIndex.cpp
  DEPENDS clang-attr-has-attribute-impl

  MODULE clang-attr-ast-visitor
  ClangAttrASTVisitor.cpp
  DEPENDS clang-attr-has-attribute-impl

  MODULE clang-attr-parser-string-switches
  ClangAttrParserStringSwitches.cpp
  DEPENDS clang-attr-has-attribute-impl

  MODULE clang-attr-text-node-dump
  ClangAttrTextNodeDump.cpp
  DEPENDS clang-attr-has-attribute-impl

  MODULE attr-docs
  AttrDocs.cpp
  DEPENDS clang-attr-has-attribute-impl

  MODULE clang-attr-subject-match-rule-list
  ClangAttrSubjectMatchRuleList.cpp
  DEPENDS clang-attr-has-attribute-impl

  MODULE clang-attr-parsed-attr-kinds
  ClangAttrParsedAttrKinds.cpp
  DEPENDS clang-attr-has-attribute-impl

  MODULE clang-attr-template-instantiate
  ClangAttrTemplateInstantiate.cpp
  DEPENDS clang-attr-has-attribute-impl

  MODULE clang-attr-parsed-attr-list
  ClangAttrParsedAttrList.cpp
  DEPENDS clang-attr-has-attribute-impl

  MODULE arm-fp16
  ArmFP16.cpp
  NeonEmitter.cpp
  SHARED

  MODULE arm-neon-sema
  ArmNeonSema.cpp
  DEPENDS arm-fp16

  MODULE arm-bf16
  ArmBF16.cpp
  DEPENDS arm-fp16

  MODULE arm-neon-test
  ArmNeonTest.cpp
  DEPENDS arm-fp16

  MODULE arm-neon
  ArmNeon.cpp
  DEPENDS arm-fp16

  MODULE arm-mve-builtin-sema
  ArmMveBuiltinSema.cpp
  MveEmitter.cpp
  SHARED

  MODULE arm-cde-builtin-def
  ArmCdeBuiltinDef.cpp
  DEPENDS arm-mve-builtin-sema

  MODULE arm-cde-header
  ArmCdeHeader.cpp
  DEPENDS arm-mve-builtin-sema

  MODULE arm-mve-builtin-codegen
  ArmMveBuiltinCG.cpp
  DEPENDS arm-mve-builtin-sema

  MODULE arm-cde-builtin-aliases
  ArmCdeBuiltinAliases.cpp
  DEPENDS arm-mve-builtin-sema

  MODULE arm-mve-builtin-def
  ArmMveBuiltinDef.cpp
  DEPENDS arm-mve-builtin-sema

  MODULE arm-mve-header
  ArmMveHeader.cpp
  DEPENDS arm-mve-builtin-sema

  MODULE arm-mve-builtin-aliases
  ArmMveBuiltinAliases.cpp
  DEPENDS arm-mve-builtin-sema

  MODULE arm-cde-builtin-codegen
  ArmCdeBuiltinCG.cpp
  DEPENDS arm-mve-builtin-sema

  MODULE arm-cde-builtin-sema
  ArmCdeBuiltinSema.cpp
  DEPENDS arm-mve-builtin-sema
  )
set_target_properties(clang-tblgen PROPERTIES FOLDER "Clang tablegenning")

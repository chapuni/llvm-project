set(LLVM_ENABLE_TABLEGEN_MODULARIZED ON)

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

  MODULE clang-sa-checkers
  ClangSACheckers.cpp
  ClangSACheckersEmitter.cpp

  MODULE clang-syntax-node-classes
  ClangSyntaxEmitter.cpp
  ClangSyntaxNodeClasses.cpp
  SHARED

  MODULE clang-syntax-node-list
  ClangSyntaxNodeList.cpp
  DEPENDS clang-syntax-node-classes

  MODULE clang-opcodes
  ClangOpcodes.cpp
  ClangOpcodesEmitter.cpp

  MODULE opt-docs
  ClangOptionDocEmitter.cpp
  OptDocs.cpp

  MODULE clang-data-collectors
  ClangDataCollectorsEmitter.cpp
  DataCollectors.cpp

  MODULE clang-comment-html-tags
  ClangCommentHTMLTags.cpp
  ClangCommentHTMLTagsEmitter.cpp
  SHARED

  MODULE clang-comment-html-tags-properties
  ClangCommentHTMLTagsProperties.cpp
  DEPENDS clang-comment-html-tags

  MODULE clang-comment-command-list
  ClangCommentCommandInfoEmitter.cpp
  ClangCommentCommandList.cpp
  SHARED

  MODULE clang-comment-command-info
  ClangCommentCommandInfo.cpp
  DEPENDS clang-comment-command-list

  MODULE clang-comment-html-named-character-references
  ClangCommentHTMLNamedCharacterReferenceEmitter.cpp
  ClangCommentHTMLNamedCharacterReferences.cpp

  MODULE clang-decl-nodes
  ClangASTNodesEmitter.cpp
  ClangDeclNodes.cpp
  SHARED

  MODULE clang-comment-nodes
  ClangCommentNodes.cpp
  DEPENDS clang-decl-nodes

  MODULE clang-stmt-nodes
  ClangStmtNodes.cpp
  DEPENDS clang-decl-nodes

  MODULE clang-type-nodes
  ASTTableGen.cpp
  ClangTypeNodes.cpp
  ClangTypeNodesEmitter.cpp
  SHARED

  MODULE clang-basic-writer
  ClangASTPropertiesEmitter.cpp
  ClangBasicWriter.cpp
  DEPENDS clang-type-nodes
  SHARED

  MODULE clang-type-reader
  ClangTypeReader.cpp
  DEPENDS clang-basic-writer

  MODULE clang-type-writer
  ClangTypeWriter.cpp
  DEPENDS clang-basic-writer

  MODULE clang-basic-reader
  ClangBasicReader.cpp
  DEPENDS clang-basic-writer

  MODULE clang-diag-groups
  ClangDiagGroups.cpp
  ClangDiagnosticsEmitter.cpp
  SHARED

  MODULE clang-diags-index-name
  ClangDiagsIndexName.cpp
  DEPENDS clang-diag-groups

  MODULE diag-docs
  DiagDocs.cpp
  DEPENDS clang-diag-groups

  MODULE clang-diags-defs
  ClangDiagsDefs.cpp
  DEPENDS clang-diag-groups

  MODULE arm-sve-sema-rangechecks
  ArmSveRangeChecks.cpp
  SveEmitter.cpp
  SHARED

  MODULE arm-sve-builtins
  ArmSveBuiltins.cpp
  DEPENDS arm-sve-sema-rangechecks

  MODULE arm-sve-header
  ArmSveHeader.cpp
  DEPENDS arm-sve-sema-rangechecks

  MODULE arm-sve-typeflags
  ArmSveTypeFlags.cpp
  DEPENDS arm-sve-sema-rangechecks

  MODULE arm-sve-builtin-codegen
  ArmSveBuiltinCG.cpp
  DEPENDS arm-sve-sema-rangechecks

  MODULE attr-docs
  AttrDocs.cpp
  ClangAttrEmitter.cpp
  SHARED

  MODULE clang-attr-parsed-attr-impl
  ClangAttrParsedAttrImpl.cpp
  DEPENDS attr-docs

  MODULE clang-attr-spelling-index
  ClangAttrSpellingListIndex.cpp
  DEPENDS attr-docs

  MODULE clang-attr-parsed-attr-kinds
  ClangAttrParsedAttrKinds.cpp
  DEPENDS attr-docs

  MODULE clang-attr-subject-match-rules-parser-string-switches
  ClangAttrSubjectMatchRulesParserStringSwitches.cpp
  DEPENDS attr-docs

  MODULE clang-attr-impl
  ClangAttrImpl.cpp
  DEPENDS attr-docs

  MODULE clang-opencl-builtins
  ClangOpenCLBuiltins.cpp
  DEPENDS attr-docs

  MODULE clang-test-pragma-attribute-supported-attributes
  TestPragmaAttributeSupportedAttributes.cpp
  DEPENDS attr-docs

  MODULE clang-attr-classes
  ClangAttrClasses.cpp
  DEPENDS attr-docs
  MODULE clang-attr-template-instantiate
  ClangAttrTemplateInstantiate.cpp
  DEPENDS attr-docs

  MODULE clang-attr-node-traverse
  ClangAttrNodeTraverse.cpp
  DEPENDS attr-docs

  MODULE clang-attr-text-node-dump
  ClangAttrTextNodeDump.cpp
  DEPENDS attr-docs

  MODULE clang-attr-ast-visitor
  ClangAttrASTVisitor.cpp
  DEPENDS attr-docs

  MODULE clang-attr-subject-match-rule-list
  ClangAttrSubjectMatchRuleList.cpp
  DEPENDS attr-docs

  MODULE clang-attr-list
  ClangAttrList.cpp
  DEPENDS attr-docs

  MODULE arm-cde-builtin-def
  ArmCdeBuiltinDef.cpp
  DEPENDS attr-docs

  MODULE clang-attr-has-attribute-impl
  ClangAttrHasAttributeImpl.cpp
  DEPENDS attr-docs

  MODULE clang-attr-pch-write
  ClangAttrPCHWrite.cpp
  DEPENDS attr-docs

  MODULE clang-attr-parser-string-switches
  ClangAttrParserStringSwitches.cpp
  DEPENDS attr-docs

  MODULE clang-attr-parsed-attr-list
  ClangAttrParsedAttrList.cpp
  DEPENDS attr-docs

  MODULE clang-attr-pch-read
  ClangAttrPCHRead.cpp
  DEPENDS attr-docs

  MODULE arm-neon-sema
  ArmNeonSema.cpp
  NeonEmitter.cpp
  SHARED

  MODULE arm-neon
  ArmNeon.cpp
  DEPENDS arm-neon-sema

  MODULE arm-fp16
  ArmFP16.cpp
  DEPENDS arm-neon-sema

  MODULE arm-bf16
  ArmBF16.cpp
  DEPENDS arm-neon-sema

  MODULE arm-neon-test
  ArmNeonTest.cpp
  DEPENDS arm-neon-sema

  MODULE arm-cde-builtin-codegen
  ArmCdeBuiltinCG.cpp
  MveEmitter.cpp
  SHARED

  MODULE arm-mve-header
  ArmMveHeader.cpp
  DEPENDS arm-cde-builtin-codegen

  MODULE arm-mve-builtin-codegen
  ArmMveBuiltinCG.cpp
  DEPENDS arm-cde-builtin-codegen

  MODULE arm-mve-builtin-aliases
  ArmMveBuiltinAliases.cpp
  DEPENDS arm-cde-builtin-codegen

  MODULE arm-cde-header
  ArmCdeHeader.cpp
  DEPENDS arm-cde-builtin-codegen

  MODULE arm-mve-builtin-sema
  ArmMveBuiltinSema.cpp
  DEPENDS arm-cde-builtin-codegen

  MODULE arm-cde-builtin-sema
  ArmCdeBuiltinSema.cpp
  DEPENDS arm-cde-builtin-codegen

  MODULE arm-cde-builtin-aliases
  ArmCdeBuiltinAliases.cpp
  DEPENDS arm-cde-builtin-codegen

  MODULE arm-mve-builtin-def
  ArmMveBuiltinDef.cpp
  DEPENDS arm-cde-builtin-codegen
  )
set_target_properties(clang-tblgen PROPERTIES FOLDER "Clang tablegenning")

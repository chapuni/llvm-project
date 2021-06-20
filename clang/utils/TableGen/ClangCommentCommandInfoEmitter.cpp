//===--- ClangCommentCommandInfoEmitter.cpp - Generate command lists -----====//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This tablegen backend emits command lists and efficient matchers for command
// names that are used in documentation comments.
//
//===----------------------------------------------------------------------===//

#include "TableGenBackends.h"

#include "llvm/TableGen/Record.h"
#include "llvm/TableGen/StringMatcher.h"
#include "llvm/TableGen/TableGenBackend.h"
#include <vector>

using namespace llvm;

namespace {
void EmitClangCommentCommandInfo(RecordKeeper &Records, raw_ostream &OS) {
  emitSourceFileHeader("A list of commands useable in documentation "
                       "comments", OS);

  OS << "namespace {\n"
        "const CommandInfo Commands[] = {\n";
  std::vector<Record *> Tags = Records.getAllDerivedDefinitions("Command");
  for (size_t i = 0, e = Tags.size(); i != e; ++i) {
    Record &Tag = *Tags[i];
    OS << "  { "
       << "\"" << Tag.getValueAsString("Name") << "\", "
       << "\"" << Tag.getValueAsString("EndCommandName") << "\", "
       << i << ", "
       << Tag.getValueAsInt("NumArgs") << ", "
       << Tag.getValueAsBit("IsInlineCommand") << ", "
       << Tag.getValueAsBit("IsBlockCommand") << ", "
       << Tag.getValueAsBit("IsBriefCommand") << ", "
       << Tag.getValueAsBit("IsReturnsCommand") << ", "
       << Tag.getValueAsBit("IsParamCommand") << ", "
       << Tag.getValueAsBit("IsTParamCommand") << ", "
       << Tag.getValueAsBit("IsThrowsCommand") << ", "
       << Tag.getValueAsBit("IsDeprecatedCommand") << ", "
       << Tag.getValueAsBit("IsHeaderfileCommand") << ", "
       << Tag.getValueAsBit("IsEmptyParagraphAllowed") << ", "
       << Tag.getValueAsBit("IsVerbatimBlockCommand") << ", "
       << Tag.getValueAsBit("IsVerbatimBlockEndCommand") << ", "
       << Tag.getValueAsBit("IsVerbatimLineCommand") << ", "
       << Tag.getValueAsBit("IsDeclarationCommand") << ", "
       << Tag.getValueAsBit("IsFunctionDeclarationCommand") << ", "
       << Tag.getValueAsBit("IsRecordLikeDetailCommand") << ", "
       << Tag.getValueAsBit("IsRecordLikeDeclarationCommand") << ", "
       << /* IsUnknownCommand = */ "0"
       << " }";
    if (i + 1 != e)
      OS << ",";
    OS << "\n";
  }
  OS << "};\n"
        "} // unnamed namespace\n\n";

  std::vector<StringMatcher::StringPair> Matches;
  for (size_t i = 0, e = Tags.size(); i != e; ++i) {
    Record &Tag = *Tags[i];
    std::string Name = std::string(Tag.getValueAsString("Name"));
    std::string Return;
    raw_string_ostream(Return) << "return &Commands[" << i << "];";
    Matches.emplace_back(std::move(Name), std::move(Return));
  }

  OS << "const CommandInfo *CommandTraits::getBuiltinCommandInfo(\n"
     << "                                         StringRef Name) {\n";
  StringMatcher("Name", Matches, OS).Emit();
  OS << "  return nullptr;\n"
     << "}\n\n";
}

TableGen::Action Action(EmitClangCommentCommandInfo,
                        "gen-clang-comment-command-info",
                        "Generate command properties for commands that are "
                        "used in documentation comments");
} // namespace

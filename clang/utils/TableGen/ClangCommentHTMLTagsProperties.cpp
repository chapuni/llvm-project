#include "TableGenBackends.h"
#include "llvm/TableGen/Main.h"
#include "llvm/TableGen/Record.h"
#include "llvm/TableGen/StringMatcher.h"
#include "llvm/TableGen/TableGenBackend.h"

using namespace llvm;

namespace {
void EmitClangCommentHTMLTagsProperties(RecordKeeper &Records,
                                        raw_ostream &OS) {
  std::vector<Record *> Tags = Records.getAllDerivedDefinitions("Tag");
  std::vector<StringMatcher::StringPair> MatchesEndTagOptional;
  std::vector<StringMatcher::StringPair> MatchesEndTagForbidden;
  for (Record *Tag : Tags) {
    std::string Spelling = std::string(Tag->getValueAsString("Spelling"));
    StringMatcher::StringPair Match(Spelling, "return true;");
    if (Tag->getValueAsBit("EndTagOptional"))
      MatchesEndTagOptional.push_back(Match);
    if (Tag->getValueAsBit("EndTagForbidden"))
      MatchesEndTagForbidden.push_back(Match);
  }

  emitSourceFileHeader("HTML tag properties", OS);

  OS << "bool isHTMLEndTagOptional(StringRef Name) {\n";
  StringMatcher("Name", MatchesEndTagOptional, OS).Emit();
  OS << "  return false;\n"
     << "}\n\n";

  OS << "bool isHTMLEndTagForbidden(StringRef Name) {\n";
  StringMatcher("Name", MatchesEndTagForbidden, OS).Emit();
  OS << "  return false;\n"
     << "}\n\n";
}

TableGen::Action Action(EmitClangCommentHTMLTagsProperties,
                        "gen-clang-comment-html-tags-properties",
                        "Generate efficient matchers for HTML tag properties");
} // namespace

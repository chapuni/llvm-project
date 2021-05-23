#include "TableGenBackends.h"
#include "llvm/TableGen/Main.h"
#include "llvm/TableGen/Record.h"
#include "llvm/TableGen/TableGenBackend.h"

using namespace llvm;

namespace {

static std::string MangleName(StringRef Str) {
  std::string Mangled;
  for (unsigned i = 0, e = Str.size(); i != e; ++i) {
    switch (Str[i]) {
    default:
      Mangled += Str[i];
      break;
    case '[':
      Mangled += "lsquare";
      break;
    case ']':
      Mangled += "rsquare";
      break;
    case '{':
      Mangled += "lbrace";
      break;
    case '}':
      Mangled += "rbrace";
      break;
    case '$':
      Mangled += "dollar";
      break;
    case '/':
      Mangled += "slash";
      break;
    }
  }
  return Mangled;
}

void EmitClangCommentCommandList(RecordKeeper &Records, raw_ostream &OS) {
  emitSourceFileHeader("A list of commands useable in documentation "
                       "comments",
                       OS);

  OS << "#ifndef COMMENT_COMMAND\n"
     << "#  define COMMENT_COMMAND(NAME)\n"
     << "#endif\n";

  std::vector<Record *> Tags = Records.getAllDerivedDefinitions("Command");
  for (size_t i = 0, e = Tags.size(); i != e; ++i) {
    Record &Tag = *Tags[i];
    std::string MangledName = MangleName(Tag.getValueAsString("Name"));

    OS << "COMMENT_COMMAND(" << MangledName << ")\n";
  }
}

TableGen::Action
    Action(EmitClangCommentCommandList, "gen-clang-comment-command-list",
           "Generate list of commands that are used in documentation comments");
} // namespace

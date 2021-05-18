//===- EnumModules.cpp ----------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "EnumModules.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Lex/HeaderSearch.h"
#include "clang/Tooling/CompilationDatabase.h"
#include "clang/Tooling/Tooling.h"
#include "llvm/Support/JSON.h"
#include "llvm/Support/Path.h"

using namespace clang;

namespace {

class EnumModulesAction : public tooling::ToolAction {
public:

  bool runInvocation(std::shared_ptr<CompilerInvocation> Invocation,
                     FileManager *FileMgr,
                     std::shared_ptr<PCHContainerOperations> PCHContainerOps,
                     DiagnosticConsumer *DiagConsumer) override {
    // Create a compiler instance to handle the actual work.
    CompilerInstance Compiler(std::move(PCHContainerOps));
    Compiler.setInvocation(std::move(Invocation));

    // Don't print 'X warnings and Y errors generated'.
    Compiler.getDiagnosticOpts().ShowCarets = false;
    // Create the compiler's actual diagnostics engine.
    Compiler.createDiagnostics(DiagConsumer, /*ShouldOwnClient=*/false);
    if (!Compiler.hasDiagnostics())
      return false;

    // Use the dependency scanning optimized file system if we can.
    //FileMgr->getFileSystemOpts().WorkingDir = std::string(WorkingDirectory);
    Compiler.setFileManager(FileMgr);
    Compiler.createSourceManager(*FileMgr);

    // Consider different header search and diagnostic options to create
    // different modules. This avoids the unsound aliasing of module PCMs.
    //
    // TODO: Implement diagnostic bucketing and header search pruning to reduce
    // the impact of strict context hashing.
    // Compiler.getHeaderSearchOpts().ModulesStrictContextHash = true;

#if 0
    auto Action = std::make_unique<InitOnlyAction>();
    //auto Action = std::make_unique<DumpCompilerOptionsAction>();
    const bool Result = Compiler.ExecuteAction(*Action);
#else
    auto Action = std::make_unique<PreprocessOnlyAction>();
    const bool Result = Compiler.ExecuteAction(*Action);
#endif
    if (!Result) return false;
    //FileMgr->clearStatCache();
#if 0
    fprintf(stderr, "%d:PP=%d\n", __LINE__, Compiler.hasPreprocessor());
    auto& PP = Compiler.getPreprocessor();
    auto& HS = PP.getHeaderSearchInfo();
    llvm::SmallVector<Module*, 12> mmm;
    HS.collectAllModules(mmm);
    fprintf(stderr, "%zu\n", mmm.size());
    for (auto m : mmm) {
      fprintf(stderr, "%d<%s><%s>\n",
	      m->isAvailable(),
	      m->getFullModuleName().c_str(), HS.getCachedModuleFileName(m).c_str());
      for (const auto fe : m->getTopHeaders(*FileMgr)) {
	fprintf(stderr, "\tT %s<%s>\n", std::string(fe->getName()).c_str(), std::string(fe->tryGetRealPathName()).c_str());
      }
      //m->print(llvm::errs());
      for (auto sm : m->submodules()) {
	fprintf(stderr, "\t%d<%s>\n",
		sm->isAvailable(),
		sm->getFullModuleName().c_str());
	for (const auto fe : sm->getTopHeaders(*FileMgr)) {
	  fprintf(stderr, "\t\tS %s<%s>\n", std::string(fe->getName()).c_str(), std::string(fe->tryGetRealPathName()).c_str());
	}
	assert(sm->submodules().size() == 0);
      }
    }
#endif

#if 1
#if 0
    std::map<std::string,
	     std::map<llvm::StringRef,
		      std::set<Module *>>> modsInMaps;

    llvm::json::Object ooo;
#endif
    llvm::json::Object outMods;
    llvm::json::Object outHashes;

    auto& PP = Compiler.getPreprocessor();
    auto& HS = PP.getHeaderSearchInfo();
    llvm::SmallVector<Module*, 12> mods;
    HS.collectAllModules(mods);
    for (auto mod : mods) {
      auto map = HS.getModuleMap().getModuleMapFileForUniquing(mod);
      std::string modFileName = HS.getCachedModuleFileName(mod);
      llvm::StringRef dir(llvm::sys::path::parent_path(StringRef(modFileName)));
      llvm::StringRef hash(*llvm::sys::path::rbegin(dir));
      dir = llvm::sys::path::parent_path(dir);
      llvm::StringRef fn(llvm::sys::path::filename(StringRef(modFileName)));
      if (!mod->isAvailable()) continue;
#if 0
      modsInMaps[std::string(dir)][map->getName()].insert(mod);
#endif
      llvm::json::Object recMod {
        {"filename", std::string(fn)},
        {"modulemap", map->getName()},
      };
      outMods[mod->getFullModuleName()] = std::move(recMod);
      llvm::json::Object recHash
        {
         {"dir", std::string(dir)},
        };
      outHashes[std::string(hash)] = std::move(recHash);
    }

    llvm::json::Object root {
      {"modules", std::move(outMods)},
      {"hashes", std::move(outHashes)},
    };

    llvm::outs() << llvm::formatv("{0:2}\n", llvm::json::Value(std::move(root)));
#endif

    return true;
  }
};

} // end anonymous namespace

bool EnumModules(const clang::tooling::CompilationDatabase &CDB) {
  tooling::ClangTool Tool(CDB, CDB.getAllFiles().front());
  Tool.mapVirtualFile("/tmp/foo.cc", "");
  Tool.clearArgumentsAdjusters();
  EnumModulesAction Action;
  return Tool.run(&Action);
}

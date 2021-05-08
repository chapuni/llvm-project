//===--- EnumModules.h - ----------------------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_TOOLS_CLANG_SCANDEPS_ENUM_MODULES_H
#define LLVM_CLANG_TOOLS_CLANG_SCANDEPS_ENUM_MODULES_H

namespace clang {
  namespace tooling {
    class CompilationDatabase;
  }
}

#include <string>

extern bool EnumModules(const clang::tooling::CompilationDatabase &CDB);

#endif // LLVM_CLANG_TOOLS_CLANG_SCANDEPS_ENUM_MODULES_H

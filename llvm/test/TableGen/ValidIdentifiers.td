// RUN: llvm-tblgen -gen-ctags %s | FileCheck %s
// XFAIL: vg_leak

// Ensure that generated names for anonymous records are valid identifiers via the ctags index.

class foo<int X> { int THEVAL = X; }
// CHECK-DAG: {{^X }}

def : foo<2>;
// CHECK-DAG: {{^\$anon\$0 }}

def X {
  foo Y = foo<1>;
}
// CHECK-DAG: {{^\$foo\$0 }}
// CHECK-DAG: {{^foo }}

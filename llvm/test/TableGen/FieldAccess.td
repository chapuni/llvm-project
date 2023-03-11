// RUN: llvm-tblgen %s | FileCheck %s
// XFAIL: vg_leak

// CHECK: --- Defs ---

// CHECK: def $Bla$0 {
// CHECK:   string blu = "";
// CHECK: }

// CHECK: def a {
// CHECK:   Bla bla = $Bla$0;
// CHECK: }

// CHECK: def b {
// CHECK:   string blu = "";
// CHECK: }

// CHECK: def c {
// CHECK:   string blu = "";
// CHECK: }

class Bla<string t>
{
  string blu = t;
}

class Bli<Bla t>
{
  Bla bla = t;
}

def a : Bli<Bla<"">>;
def b : Bla<!cast<Bla>(a.bla).blu>;
def c : Bla<a.bla.blu>;

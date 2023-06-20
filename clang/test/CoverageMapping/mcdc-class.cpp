// RUN: %clang_cc1 -triple %itanium_abi_triple -std=c++11 -fcoverage-mcdc -fprofile-instrument=clang -fcoverage-mapping -dump-coverage-mapping -emit-llvm-only %s | FileCheck %s

extern void foo();
extern void bar();
class Value {
     public:
        void setValue( int len );
        int getValue( void );
        Value();   // This is the constructor declaration
        ~Value();  // This is the destructor declaration
  
     private:
        int value;
  };
  
  // Member functions definitions including constructor
  Value::Value(void) {
      if (value == 2 || value == 6)
          foo();
  }
  Value::~Value(void) {
      if (value == 2 || value == 3)
          bar();
  }

// CHECK:  Decision,File 0, 18:11 -> 18:35 = M:0, C:2
// CHECK:  Branch,File 0, 18:11 -> 18:21 = (#0 - #2), #2 [1,0,2]
// CHECK:  Branch,File 0, 18:25 -> 18:35 = (#2 - #3), #3 [2,0,0]
// CHECK:  Decision,File 0, 22:11 -> 22:35 = M:0, C:2
// CHECK:  Branch,File 0, 22:11 -> 22:21 = (#0 - #2), #2 [1,0,2]
// CHECK:  Branch,File 0, 22:25 -> 22:35 = (#2 - #3), #3 [2,0,0]

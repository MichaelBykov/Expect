#include <Expect>

struct Bar {
  int x;
  
  Bar(int x) : x(x) { }
};

struct Foo {
  Bar *bar;
  
  Foo() : bar(nullptr) { }
  
  Foo(Bar *bar) : bar(bar) { }
};

SUITE(Tests) {
  SHARE {
    int someValue;
    Foo foo;
    int *z;
  };
  
  SETUP {
    SHARED someValue = 3;
    SHARED z = new int(1964);
    SHARED foo = Foo(new Bar(21));
  };
  
  TEARDOWN {
    delete SHARED foo.bar;
    delete SHARED z;
  };
  
  int loopCount = 10;
  
  TEST(foo, "Example test.") {
    EXPECT SHARED someValue == 3;
    for (int i = 0; i < loopCount; i++)
      EXPECT SHARED foo.bar->x == 21;
    EXPECT *SHARED z == 1964;
    
    EXPECT_EXCEPTION(int) { throw 3; };
  };
}

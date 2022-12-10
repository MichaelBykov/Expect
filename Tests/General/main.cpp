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

#define EXPECT_TEST_FAIL(expression) \
  EXPECT_EXCEPTION(NAMESPACE_EXPECT TestFailedException) { expression; } \
    | "The test did not fail.";

#define EXPECT_TEST_OKAY(expression) \
  EXPECT_NO_EXCEPTION { expression; } \
    | "The test did not succeed.";

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
    EXPECT_TEST_FAIL(ASSERT_EXCEPTION(int) { throw ""; });
    EXPECT_TEST_OKAY(ASSERT_EXCEPTION(const char *) { throw ""; });
    
    EXPECT_TEST_FAIL(ASSERT_ANY_EXCEPTION { });
    EXPECT_TEST_OKAY(ASSERT_ANY_EXCEPTION { throw 3; });
    
    EXPECT_TEST_OKAY(ASSERT_NO_EXCEPTION { });
    EXPECT_TEST_FAIL(ASSERT_NO_EXCEPTION { throw 3; });
    
    // EXPECT_WITHIN 1.0 < 0.1 | "foo" | 0.1;
    
    // EXPECT SHARED someValue == 4 | "Something's fishy here...";
    // for (int i = 0; i < loopCount; i++)
    //   EXPECT SHARED foo.bar->x == 21;
    // EXPECT *SHARED z == 1964;
    
    // EXPECT_EXCEPTION(int) { throw ""; } | "Shouldn't be a string.";
    // EXPECT false | "A fail message";
  };
}

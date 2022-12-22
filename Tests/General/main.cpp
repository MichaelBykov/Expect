#include <Expect>
USE_EXPECT_MATCHING

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
    // EXPECT_TEST_FAIL(ASSERT_EXCEPTION(int) { throw ""; });
    // EXPECT_TEST_OKAY(ASSERT_EXCEPTION(const char *) { throw ""; });
    
    // EXPECT_TEST_FAIL(ASSERT_ANY_EXCEPTION { });
    // EXPECT_TEST_OKAY(ASSERT_ANY_EXCEPTION { throw 3; });
    
    // EXPECT_TEST_OKAY(ASSERT_NO_EXCEPTION { });
    // EXPECT_TEST_FAIL(ASSERT_NO_EXCEPTION { throw 3; });
    
    EXPECT false | MESSAGE "foo " << 3 << '.';
    
    EXPECT_THAT 3 | inRange(1, 2) | isEven | isEven<int>() xor isEven | inRange(0, 1) or not isEven<int>() and not inRange(-1, 1) | MESSAGE "Something's fishy. " << 3 << " is fishy." | not isEven<int>() and inRange(-100, 0) | inRange(1, 3) and not isEven<int>() | isEven | "foo" | isEven or isEven;
    
    std::vector<int> vector = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1 };
    EXPECT_THAT vector | not not each<std::vector<int>, int>([](int element) { return element % 2 == 0; }) | each<std::vector<int>>(1);
    EXPECT_THAT (int *)nullptr | isNull<int *>() | isNull<int *>() or isNull<int *>() | isNull;
    EXPECT_THAT vector | each<std::vector<int>>(1);
    EXPECT_THAT nullptr | isNull | isNull<nullptr_t>() ^ isSome;
    
    
    // EXPECT_THAT, (((((builder << X | a) and (b | b)) and (c | c)) or ((d | f) and (g | f))) or h);
    //
    // builder << X | a
    //    AND
    //        (b | b)
    // ..
    // builder << X | (a and b) | b
    //    AND
    //        (c | c)
    // ..
    // builder << X | (a and b) | (b and c) | c
    //    OR
    //        (d | f) and (g | f)
    // builder << X | (a and b) | (b and c) | (c or d) | (f and g) | f
    //    OR
    //        h
    // ..
    // builder << X | (a and b) | (b and c) | (c or d) | (f and g) | (f or h)
    //
    //
    //
    //
    // builder << X | a
    //    AND
    //        b {right: b}
    // .. builder << X | (a and b)
    //    {right: b}
    // builder << X | (a and b) | b
    //    AND
    //        c {right: c}
    // .. builder << X | (a and b) | (b and c)
    //    {right: c}
    // builder << X | (a and b) | (b and c) | c
    //    OR
    //        (d {right: f} and g {right: f}) and k {right: f}
    // .. builder << X | (a and b) | (b and c) | (c or d)
    //    {right: f}
    //    AND
    //        g {right: f} and k {right: f}
    // .. builder << X | (a and b) | (b and c) | (c or d) | f
    //    AND
    //        g {right: f} and k {right: f}
    // .. builder << X | (a and b) | (b and c) | (c or d) | (f and g)
    //    {right: f}
    //    AND
    //        k {right: f}
    // .. builder << X | (a and b) | (b and c) | (c or d) | (f and g) | f
    //    AND
    //        k {right: f}
    // .. builder << X | (a and b) | (b and c) | (c or d) | (f and g) | (f and k)
    //    {right: f}
    // builder << X | (a and b) | (b and c) | (c or d) | (f and g) | (f and k) | f
    
    // EXPECT_EXCEPTION_THAT()
    
    // EXPECT_THAT "foo" | matches() && !explains() | startsWith();
    
    // SECTION {
    //   ASSERT false;
    //   EXPECT false;
    // };
    
    // EXPECT false;
    
    // EXPECT_WITHIN 1.0 < 0.1 | "foo" | 0.1;
    
    // EXPECT SHARED someValue == 4 | "Something's fishy here...";
    // for (int i = 0; i < loopCount; i++)
    //   EXPECT SHARED foo.bar->x == 21;
    // EXPECT *SHARED z == 1964;
    
    // EXPECT_EXCEPTION(int) { throw ""; } | "Shouldn't be a string.";
    // EXPECT false | "A fail message";
  };
}

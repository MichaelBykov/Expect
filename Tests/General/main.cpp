#include <Expect>

SUITE(Tests) {
  int someValue;
  
  SETUP {
    someValue = 3;
  };
  
  TEARDOWN {
    printf("%d\n", someValue);
  };
  
  TEST(foo, "Example test.") {
    printf("%d\n", someValue);
  };
}

# `SECTION` macro

## Jump to...
- [Availability](#Availability)
- [Syntax](#Syntax)
- [Parameters and Contents](#Parameters-and-Contents)
- [Usage](#Usage)
- [Examples](#Examples)
- [See Also](#See-Also)

## Availability
Since 1.0.0

## Syntax
``` C++
SECTION {
  [contents]
};
```

## Parameters and Contents
- `[contents]` : The contents of the test section including assertions.

## Usage

Creates an isolated test subsection that can have fatal assertions that only
stop the rest of the section from executing rather than the whole test case.
Useful when wanting check a precondition before executing further assertions.

## Examples

The below example checks a precondition before continuing to execute the rest of
the section.
``` C++
SUITE(Sections) {
  TEST(my test, "Use sections to check vectors.") {
    // Run an isolated section that doesn't affect the execution of the rest of
    // the test case
    SECTION {
      std::vector<int> range = generateRange(10);
      
      // If the below assertion fails, only the section will stop executing,
      // not the whole test case
      ASSERT range.size() == 10;
      
      // Since range is guaranteed to have 10 elements now, we don't have to
      // worry about out-of-bounds access
      for (int i = 0; i < 10; i++)
        EXPECT range[i] == i;
    };
    
    // Since the above section isolates its fatal assertions, if the above
    // range.size() assertion failed, we could still continue to run the test
    // case including the section below
    SECTION {
      std::vector<int> range = generateRange(1000);
      
      ASSERT range.size() == 1000;
      
      for (int i = 0; i < 1000; i++)
        EXPECT range[i] == i;
    };
  };
}
```

## See Also

- [Assertions](../Assertions)
  - A list of all the different assertion macros that can be used inside of test
    cases and sections.
- [`TEST` macro](TEST.md)
  - Define a test case.
- [Creating a test case tutorial](../../Tutorials/Intro/TestCase.md)
  - Learn to setup and run a test case.

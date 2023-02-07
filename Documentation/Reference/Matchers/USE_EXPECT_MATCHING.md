# `USE_EXPECT_MATCHING` macro

## Jump to...
- [Availability](#Availability)
- [Syntax](#Syntax)
- [Usage](#Usage)
- [Examples](#Examples)
- [See Also](#See-Also)

## Availability
Since 1.0.0

## Syntax
``` C++
#include <Expect>
USE_EXPECT_MATCHING
```

## Usage

Use the default Expect matchers.

Equivalent to `using namespace` statements for all Expect matcher namespaces.

## Examples

The below example demonstrates using the default Expect matchers.
``` C++
#include <Expect>
USE_EXPECT_MATCHING

// ... inside a test case

EXPECT_THAT value | isNonNaN;
// ^ no need to state Expect::Matchers::isNonNaN
```

## See Also

- [`EXPECT_THAT` macro](EXPECT_THAT.md)
  - The standard non-fatal matcher assertion.
- [`ASSERT_THAT` macro](EXPECT_THAT.md)
  - The standard fatal matcher assertion.
- [Using Matchers](../../Tutorials/Using-Matchers.md)
  - A guided walkthrough of using matchers.

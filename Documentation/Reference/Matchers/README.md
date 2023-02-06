# Matchers - Reference

## Jump to...
- [Macros](#Macros)
- [Matchers](#Matchers)

## Macros
- [`EXPECT_THAT` macro](EXPECT_THAT.md) / [`ASSERT_THAT` macro](EXPECT_THAT.md)
  - Expect that a value matches a set of matchers.
- [`MATCHER` macro](MATCHER.md)
  - Define a custom matcher.
- [`MATCHER_RESULT` macro](MATCHER_RESULT.md)
  - Get the result of a custom matcher.
- [`USE_EXPECT_MATCHING` macro](USE_EXPECT_MATCHING.md)
  - Use default matchers.

## Matchers
- [`isA` matcher](isA.md) / [`isAn` matcher](isA.md)
  - The default type-matching matcher.
- [`isNull` matcher](isNull.md)
  - The default null matcher.
- [`isSome` matcher](isSome.md)
  - The default non-null matcher.
- [`isNaN` matcher](isNaN.md)
  - The default not-a-number matcher.
- [`isNonNaN` matcher](isNonNaN.md)
  - The default not-not-a-number matcher.
- [`isFinite` matcher](isFinite.md)
  - The default finite-number matcher.
- [`isInfinite` matcher](isInfinite.md)
  - The default infinite-number matcher.
- [`each` matcher](each.md)
  - The default predicate matcher.
- [`has` matcher](has.md)
  - The default specific-count predicate matcher.
- [`contains` matcher](contains.md)
  - The default any-count predicate matcher.
- [`beginsWith` matcher](beginsWith.md)
  - The default string prefix matcher.
- [`endsWith` matcher](endsWith.md)
  - The default string suffix matcher.

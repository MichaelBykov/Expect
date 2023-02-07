# `RUN_COMMAND_LINE_TESTS` macro

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
RUN_COMMAND_LINE_TESTS([argc], [argv]);
```

## Parameters and Contents
- `[argc]` : The standard `argc` command line argument
  (command line argument count).
- `[argv]` : The standard `argv` command line argument
  (command line argument vector).

## Usage

Run the default command line test driver for Expect.

Will return a status code for the result of the test run.

If your test cases are linked to the [AutoExpect](../../Tutorials/Building.md)
library, this will automatically be called for you.

## Examples

The below example demonstrates invoking the default test driver from the main
function.
``` C++
int main(int argc, char *argv[]) {
  return RUN_COMMAND_LINE_TESTS(argc, argv);
}
```

## See Also

- [Building Expect Tutorial](../../Tutorials/Building.md)
  - A guide to the various ways of building Expect.
- [Running Expect Tutorial](../../Tutorials/Running.md)
  - A guide to the various ways of running Expect.

# Running Expect

A guide to the various ways of running Expect.

## Jump to...
- [Overview](#Overview)
- [Interface](#Interface)
- [Runtime](#Runtime)
- [See Also](#See-Also)

## Overview

Once you have built your tests and linked them to Expect, if you linked them to
AutoExpect or used the Expect command-line driver as your own driver,
your tests can be run from the command line using the standard Expect
command-line interface.

## Interface

The Expect command-line interface has the following usage instructions for
your test executable named `test-executable`:
```
test-executable [flags...] [test-names-or-suites...]
```

The standard flags available to control the are listed below:
- `-h`, `--help` : Display help for the test driver.
- `-c`, `--continue` : Continue after failed `EXPECT` assertions.
  Will not affect the behavior of `ASSERT` assertions.
  This is enabled by default.
- `--stop` : Stop a test case after any failed assertion.

In order to run test cases there are three main options for choosing what tests
to run:
- By test suite : Run all unit test cases in a test suite by naming the test
  suite.
  Doesn't include test cases marked with the `benchmark` or `skip` tags.
- By test case : Run a specific test case by naming the test case.
- By tag : Run all test cases with a specific tag by naming the tag and
  prefixing it with the `#` symbol.
  For instance, to run all test cases with the `run-me` tag, you would add
  `#run-me` as a command-line argument.

You can combine as many the above test running options and flags in any order
you chose and provide them as command-line arguments to your test executable.
The test executable will run all of the selected tests.

## Runtime

While your tests are running, you will get the following updates posted to the
command line.
- Whenever a test suite is about to be run and when it ends.
- When a test passed and the results of any benchmarks that were run inside it.
- When a test failed and a list of the assertion failures that it experienced.
- An overview of how many of your tests were successful and how many failed.

## See Also

- [Quick Start](Quick-Start.md)
  - A guide to quickly setup and start using Expect.
- [Building](Building.md)
  - A guide to the various ways of building Expect.

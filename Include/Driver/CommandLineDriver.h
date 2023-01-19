// ===--- CommandLineDriver.h ------------------------------------ C++ ---=== //
//                                                                            //
// © 2023, Michael Bykov                                                      //
//                                                                            //
// ===--------------------------------------------------------------------=== //
//                                                                            //
// The test driver used when launching tests form the command line.           //
//                                                                            //
// ===--------------------------------------------------------------------=== //

#pragma once
#include <Expect Common.h>

START_NAMESPACE_EXPECT



int runCommandLineTests(
  int   argc  ,
  char *argv[]
);



END_NAMESPACE_EXPECT



#define RUN_COMMAND_LINE_TESTS(argc, argv) \
  NAMESPACE_EXPECT runCommandLineTests(argc, argv)

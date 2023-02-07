// ===--- Expect Common.h ---------------------------------------- C++ ---=== //
//                                                                            //
// © 2023, Michael Bykov                                                      //
//                                                                            //
// ===--------------------------------------------------------------------=== //
//                                                                            //
// A common set of macros defined for Expect.                                 //
//                                                                            //
// ===--------------------------------------------------------------------=== //

#pragma once

// For Visual Studio
#define _CRT_SECURE_NO_WARNINGS

#define START_NAMESPACE_EXPECT \
  namespace Expect {

#define END_NAMESPACE_EXPECT \
  }

#define NAMESPACE_EXPECT \
  Expect::

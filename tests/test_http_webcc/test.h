/*
* Copyright (C) 2016 Nick Naumenko (https://github.com/nnaumenko)
* All rights reserved
* This software may be modified and distributed under the terms
* of the MIT license. See the LICENSE file for details.
*/

#ifndef TEST_H
#define TEST_H

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

#define TEST_STREAM Serial

#define TEST_SETUP() do{Serial.begin(9600);}while(0)

#define TEST_FAIL() do {TEST_STREAM.print("FAILED in line "); TEST_STREAM.print(__LINE__);  TEST_STREAM.print(", file "); TEST_STREAM.println(__FILENAME__); __testFunctionResult__=false; yield();} while (0)
#define TEST_ASSERT(condition) do { if (!(condition)) {TEST_FAIL();} yield();} while(0)

#define TEST_PRINTLN(text) TEST_STREAM.println(F(#text))

#define TEST_BEGIN() do{TEST_STREAM.println("\n---------------- TESTING STARTED ----------------\n");} while(0)
#define TEST_END() do{TEST_STREAM.println("\n---------------- TESTING FINISHED ---------------"); yield();} while(0)

#define TEST_FUNC_START() bool __testFunctionResult__=true; do {TEST_STREAM.print("Test function started: "); TEST_STREAM.print(__PRETTY_FUNCTION__); TEST_STREAM.print(", file "); TEST_STREAM.println(__FILENAME__); yield(); }while(0)
#define TEST_FUNC_END() do{ if (__testFunctionResult__) TEST_STREAM.println("PASSED"); yield();} while (0)

#endif

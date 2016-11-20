# Running the tests

Copy here all necessary files from main project directory.

The files to be copied are as follows:

* diag.h
* module.h

Open .ino file in IDE, compile, upload and open serial monitor to observe test results

# Expected test results

The following is expected in serial monitor window:

    ---------------- TESTING STARTED ----------------
    
    Test function started: static void TestFakeStream::beginIn_inputInit_expectCorrectInputInBuffer(), file fakestream.cpp
    PASSED
    Test function started: static void TestFakeStream::readIn_inputRead_expectCorrectCharsRead(), file fakestream.cpp
    PASSED
    Test function started: static void TestFakeStream::readIn_inputReadUnavailable_expectUnavailable(), file fakestream.cpp
    PASSED
    Test function started: static void TestFakeStream::writeOut_printString_expectTheSameStringInTheOutBuffer(), file fakestream.cpp
    PASSED
    Test function started: static void TestFakeStream::beginInOut_inputInit_expectCorrectInputInBuffer(), file fakestream.cpp
    PASSED
    Test function started: static void TestFakeStream::readInOut_inputRead_expectCorrectCharsRead(), file fakestream.cpp
    PASSED
    Test function started: static void TestFakeStream::readInOut_inputReadUnavailable_expectUnavailable(), file fakestream.cpp
    PASSED
    Test function started: static void TestFakeStream::writeInOut_printString_expectTheSameStringInTheOutBuffer(), file fakestream.cpp
    PASSED
    Test function started: static void TestDiagLog::log_resetPrintOutput_expectNoCrash(), file test_diaglog.ino
    PASSED
    Test function started: static void TestDiagLog::log_messageSinglePart_expectTheSameString(), file test_diaglog.ino
    PASSED
    Test function started: static void TestDiagLog::log_messageMultipleParts_expectConcatenatedParts(), file test_diaglog.ino
    PASSED
    Test function started: static void TestDiagLog::log_messageSeverities_expectCorrectSeverityTexts(), file test_diaglog.ino
    PASSED
    Test function started: static void TestDiagLog::log_twoSequentialMessages_expectMessageNumberIncreases(), file test_diaglog.ino
    PASSED
    
    ---------------- TESTING FINISHED ---------------

# Failed tests

The following example illustrates failed tests reporting:

    Test function started: static void test(), file test.ino
    FAILED in line 1, file test.ino
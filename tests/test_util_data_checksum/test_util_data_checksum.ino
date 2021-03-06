#include <ESP8266WiFi.h>

#include "test.h"

#include "util_data.h"

class TestCrc16 {
  public:
    static void crc16_referenceData_expectCorrectChecksum(void) {
      TEST_FUNC_START();
      //arrange
      static const size_t maxBufferSize = 32;
      static const size_t testValues = 3;
      const struct {
        uint8_t buffer[maxBufferSize];
        size_t bufferSize;
        uint16_t polynomial;
        uint16_t referenceResult;
      } testData[testValues] = {
        {{'A', 'm', 'b', 'i', 't'}, 5, 0x8005, 0x0AAF},
        {{'1', '2', '3', '4', '5', '6', '7', '8', '9'}, 9, 0x8005, 0xBB3D},
        {{0x5F, 0xD8, 0x86, 0x80, 0x46, 0xC0, 0x5A, 0x87, 0x5B, 0xCF, 0xE2, 0x8B, 0xB8, 0xBC, 0xD3, 0x4E}, 16, 0x8005, 0xE8B8} //generated using random.org
      };
      uint16_t results[testValues];
      //act
      for (size_t i = 0; i < testValues; i++)
        results[i] = util::checksum::crc16(testData[i].buffer, testData[i].bufferSize, testData[i].polynomial);
      //assert
      for (size_t i = 0; i < testValues; i++) {
        TEST_ASSERT(results[i] == testData[i].referenceResult);
      }
      TEST_FUNC_END();

    }
    static void crc16_bufferNull_expectZero(void) {
      TEST_FUNC_START();
      //arrange
      static const size_t bufferSize = 10;
      void * buffer = NULL;
      //act
      uint16_t result = util::checksum::crc16(buffer, bufferSize);
      //assert
      TEST_ASSERT(!result); //assuming init == 0x0000
      TEST_FUNC_END();
    }
    static void crc16_bufferSizeZero_expectZero(void) {
      TEST_FUNC_START();
      //arrange
      static const size_t bufferSize = 0;
      uint8_t buffer[10];
      //act
      uint16_t result = util::checksum::crc16(buffer, bufferSize);
      //assert
      TEST_ASSERT(!result);
      TEST_FUNC_END();
    }
    static void testCrc16(void) {
      crc16_referenceData_expectCorrectChecksum();
      crc16_bufferNull_expectZero();
      crc16_bufferSizeZero_expectZero();
    }
  public:
#pragma GCC push_options
#pragma GCC optimize ("O0")
    static void testPerformanceCrc16(void) {
      PERF_TEST_FUNC_START();
      static const size_t testBufferSize = 256;
      const uint8_t testBuffer[testBufferSize] = { //generated using random.org
        0x92, 0x6C, 0x8C, 0x41, 0x23, 0x44, 0x19, 0xD3, 0x04, 0x65, 0x4E, 0x16, 0x0A, 0x46, 0xA3, 0x62,
        0x61, 0x5F, 0x3B, 0xA4, 0xED, 0xCA, 0xF0, 0x05, 0x1B, 0x9C, 0x0D, 0x14, 0x51, 0xBC, 0xF5, 0x5A,
        0x76, 0x90, 0xC8, 0x7A, 0x58, 0x97, 0x79, 0x52, 0xE4, 0x21, 0xD8, 0x60, 0x3D, 0xE6, 0x10, 0x1A,
        0x56, 0x81, 0x03, 0xFA, 0x8F, 0xBE, 0x12, 0xF6, 0x11, 0x09, 0xAD, 0xFF, 0x26, 0x7E, 0xB6, 0x9D,
        0x29, 0xC5, 0x1E, 0x59, 0x39, 0xDE, 0xF8, 0x9B, 0x6E, 0x13, 0x07, 0xCB, 0x17, 0x83, 0x1D, 0xE3,
        0xD1, 0x86, 0x37, 0xC4, 0xEB, 0xD0, 0x40, 0x84, 0x02, 0x89, 0xD2, 0xE8, 0xDA, 0x4A, 0x42, 0xAA,
        0x82, 0x2F, 0xCF, 0x50, 0x85, 0x30, 0xA5, 0x3F, 0x00, 0x6D, 0xA9, 0xCE, 0xDD, 0xC1, 0x3E, 0x4D,
        0x2C, 0x36, 0x08, 0xA0, 0xFD, 0x78, 0xBD, 0x7B, 0x27, 0x99, 0xA7, 0x2E, 0xC3, 0x77, 0x80, 0xC7,
        0x53, 0x3A, 0x18, 0x6B, 0x0B, 0x9F, 0xEA, 0x6F, 0xB0, 0x3C, 0x8A, 0xBA, 0x01, 0x96, 0x57, 0x06,
        0x7D, 0x5C, 0x93, 0x75, 0xC0, 0x7F, 0x4F, 0xEF, 0xFC, 0xE9, 0xB1, 0x34, 0x55, 0x9E, 0x63, 0x2B,
        0xF9, 0x35, 0x72, 0x24, 0x15, 0x87, 0x8D, 0xBB, 0x98, 0xA2, 0x6A, 0xAC, 0xB7, 0xB4, 0x5B, 0x33,
        0xA6, 0x88, 0x8E, 0xE5, 0x22, 0xEE, 0x94, 0x5E, 0xA1, 0x64, 0xFB, 0xCD, 0xB9, 0xA8, 0x8B, 0x38,
        0xB3, 0x5D, 0xAF, 0x47, 0x28, 0xB2, 0xAE, 0xE1, 0x0C, 0xD9, 0x45, 0xF7, 0x20, 0x7C, 0x2A, 0x67,
        0x71, 0x4C, 0x49, 0xF4, 0xE2, 0xF1, 0xDB, 0x4B, 0x91, 0xD4, 0xAB, 0xBF, 0xDF, 0x68, 0x9A, 0x48,
        0x25, 0xE0, 0xC9, 0xDC, 0xF2, 0x1C, 0x54, 0xC2, 0x69, 0xCC, 0xD7, 0x31, 0xE7, 0x0E, 0xC6, 0x70,
        0xB8, 0xB5, 0xF3, 0xFE, 0x73, 0xEC, 0x0F, 0x66, 0x95, 0x2D, 0x1F, 0x32, 0x43, 0x74, 0xD6, 0xD5
      };
      static const int numberOfOperations = 1000;
      PERF_TEST_START();
      for (int i = 0; i < numberOfOperations; i++)
        util::checksum::crc16(testBuffer, testBufferSize);;
      PERF_TEST_END();
      PERF_TEST_FUNC_END();
    }
#pragma GCC pop_options
  public:
    static void runTests(void) {
      testCrc16();
      testPerformanceCrc16();
    }
};

TEST_GLOBALS();

void setup() {
  TEST_SETUP();
  TEST_BEGIN();
  TestCrc16::runTests();
  TEST_END();
}

void loop() {
  delay(100);
}

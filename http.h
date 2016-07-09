/*
 * Copyright (C) 2016 Nick Naumenko (https://github.com/nnaumenko)
 * All rights reserved
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef HTTP_H
#define HTTP_H

#include <Arduino.h>
#include "stringmap.h"

const size_t HTTP_REQUEST_PART_MAX_SIZE = 32;

#ifdef ESP8266
#include <ESP8266WiFi.h>
#define HTTPSTREAM_OUT_BUFFER_SIZE WIFICLIENT_MAX_PACKET_SIZE
//WIFICLIENT_MAX_PACKET_SIZE is 1460, see libraries/ESP8266WiFi/src/WiFiClient.h
//smaller value might be required when porting to Arduino due to memory constraints
#endif

enum class HttpStatusCode {
  UNKNOWN = STRINGMAP_ITEM_DEFAULT,
  NO_CHANGE = STRINGMAP_ITEM_DEFAULT,
  CONTINUE = 100,
  OK = 200,
  SEE_OTHER = 303,
  BAD_REQUEST = 400,
  NOT_FOUND = 404,
  METHOD_NOT_ALLOWED = 405,
  REQUEST_URI_TOO_LONG = 414,
  INTERNAL_SERVER_ERROR = 500,
  NOT_IMPLEMENTED = 501,
};

class HttpPercentCode {
  public:
    static int decode(char buffer[]);
    static int decodeDigit(char hexDigit);
    static const int decodeError = -1;
    static const size_t size = 3; //each percent code contains exacty 3 characters
};

class HttpURL {
  public:
    static void decode(char buffer[], size_t bufferSize);
};

class HttpStream : public Stream {
  public:
    HttpStream (Stream & client);
    ~HttpStream();
  public:
    virtual int available();
    virtual int read();
    virtual int peek();
    virtual void flush();
    virtual size_t write(uint8_t character);
  public:
    void readUntil(const char * charsToFind, char * buffer, size_t bufferSize);
  private:
    Stream * client = NULL;
  public:
    static const int NOT_AVAILABLE = -1;
  private:
    char previousChar = '\0';
  private:
    void sendOutputBuffer(void);
    int outputBufferPosition = 0;
    char outputBuffer[HTTPSTREAM_OUT_BUFFER_SIZE];
  public:
};

enum class HttpRequestPart {
  NONE,
  METHOD,
  PATH,
  GET_QUERY_NAME,
  GET_QUERY_VALUE,
  VERSION,
  FIELD_NAME,
  FIELD_VALUE,
  POST_QUERY_NAME,
  POST_QUERY_VALUE,
};

class HttpReqParser;

class HttpReqPartHandler {
  public:
    void begin (HttpReqParser &parser) {
      this->parser = &parser;
    }
    virtual void execute(char * value, HttpRequestPart part) = 0;
  protected:
    HttpReqParser * parser = NULL;
};

class HttpReqParser {
  public:
    boolean begin (HttpStream &client);
    void setHandler (HttpReqPartHandler &handler);
  private:
    HttpStream * client = NULL;
    HttpReqPartHandler * reqPartHandler = NULL;
  public:
    enum class ParserState {
      UNKNOWN,
      ERROR,
      BEGIN,
      METHOD,
      PATH,
      URL_QUERY_NAME,
      URL_QUERY_VALUE,
      HTTP_VERSION,
      FIELD_OR_HEADER_END,
      FIELD_NAME,
      FIELD_VALUE,
      HEADER_END,
      POST_QUERY_OR_END,
      POST_QUERY_NAME,
      POST_QUERY_VALUE,
      FINISHED,
    };
    enum class StreamOperation {
      FLUSH,       //Flush client stream and do not read
      DO_NOTHING,  //Do not read anything from stream
      READ,        //Read from stream to buffer until expected characters (see transition table) are found
      SKIP,        //Read from stream but do not put characters to buffer until expected characters are found
      PEEK,        //Do not read anything from stream and peek (rather than read) next character
    };
  public:
    static const char CHAR_OTHER = '\0';
    static const char CHAR_UNAVAIL = (char)HttpStream::NOT_AVAILABLE;
  private:
    struct {
      HttpStatusCode statusCode;
      HttpRequestPart requestPart;
      char nextCharacter;
      ParserState currentState;
    } parserStatus;
  public:
    void parse(void);
    boolean finished(void);
    void setError(HttpStatusCode errorStatusCode);
    boolean isError(void);
    HttpStatusCode getStatusCode(void);
  private:
    void transition(ParserState newState, HttpStatusCode newStatusCode);
  private:
    class ParserTableBase {
      public:
        ParserTableBase ();
      protected:
        size_t tableSize;
      protected:
        size_t tableIndex;
        size_t getTableIndex(void);
        boolean setTableIndex(size_t newIndex);
        void firstEntry(void);
        boolean nextEntry(void);
    };
  public:
    struct ProcessingTableEntry {
      ParserState state;
      StreamOperation operation;
      HttpRequestPart part;
    };
  private:
    class ProcessingTable : ParserTableBase {
        ProcessingTableEntry * table;
        static const size_t tableEntrySize = (sizeof(table[0]));
      public:
        boolean begin (void);
        boolean find (ParserState state);
        StreamOperation getStreamOperation(void);
        HttpRequestPart getRequestPart(void);
      private:
        ParserState getState(void);
    } processingTable;
  public:
    struct TransitionTableEntry {
      ParserState state;
      char nextChar;
      ParserState newState;
      HttpStatusCode newStatusCode;
    };
  private:
    class TransitionTable : ParserTableBase {
      private:
        TransitionTableEntry * table;
        static const size_t tableEntrySize = (sizeof(table[0]));
      public:
        boolean begin (void);
        void find (ParserState state, char nextChar);
        boolean enumerateNextChars(ParserState state, char * buffer, size_t bufferSize);
        ParserState getNewState();
        HttpStatusCode getNewStatusCode();
      private:
        ParserState getState();
        char getNextChar();
    } transitionTable;
};

#endif
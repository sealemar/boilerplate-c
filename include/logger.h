// Copyright [2017] [Sergey Markelov]
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// developed by Sergey Markelov (09/14/2017)
//
// @brief logger
//

#ifndef GENERIC_LOGGER
#define GENERIC_LOGGER

#include <stdio.h>

enum LogLevel { LL_DEBUG = 0, LL_INFO, LL_WARNING, LL_ERROR };
extern const char* LogLevelStr[LL_ERROR + 1];

extern void *__logData;
extern void (*__logFunc)(void *data, enum LogLevel logLevel, const char* file, int line, const char* func, const char *format, ...);

#define LOGGER_BACKTICKS_SIZE 10

//
// @brief data structure for @see logger_stream
//
// @param errStream error stream, like stderr
// @param outStream output stream, like stdout
// @param logLevel anything below will be ignored
//
// @param format a format string, where
//      %m - log message
//      %L - log level (as passed to __logFunc function)
//      %F - file name, which emitted the message
//      %l - line in the file
//      %f - function name
//      %0 .. %9 - backtick[n]
//
//      anything else is written to the output unchanged, except for every first percent.
//
//      @example
//
//      "%%[%L] %0 - %F:%l (%f) - %m"
//      "%[LOG_LEVEL] backtick[0]() - filename:line (function) - message"
//
// @param backtics a collection of backtick functions
//      backtick function should populate outStr, which is written out
//
//      backtick function prototype is
//
//      int backtick(struct logger_streamData *logData, char *outStr, size_t sz);
//
//      where
//          @c logData - is logger_streamData
//          @c outStr  - output string where the result should be stored
//          @c sz      - size of the output buffer
//
struct logger_streamData {
    FILE          *errStream;
    FILE          *outStream;
    enum LogLevel  logLevel;
    const char    *format;
    int (*backtics[LOGGER_BACKTICKS_SIZE])(struct logger_streamData *logData, char *outStr, size_t sz);
};

void logger_stream(void *data, enum LogLevel logLevel, const char* file, int line, const char* func, const char *format, ...);

#define ERROR_PREFIX            "Error: "
#define ERROR_CONTINUE_PREFIX   " ----> "

#define Log(logLevel, format, ...) \
    { if(__logFunc) { __logFunc(__logData, logLevel, __FILE__, __LINE__, __func__, format, ##__VA_ARGS__); } }

#define LogDebug(format, ...)   { Log(LL_DEBUG,   format, ##__VA_ARGS__); }
#define LogInfo(format, ...)    { Log(LL_INFO,    format, ##__VA_ARGS__); }
#define LogWarning(format, ...) { Log(LL_WARNING, format, ##__VA_ARGS__); }
#define LogError(format, ...)   { Log(LL_ERROR,   format, ##__VA_ARGS__); }

#define LogErrorExInit(format, ...)     { LogError( "%s" format, ERROR_PREFIX,          ##__VA_ARGS__ ); }
#define LogErrorExContinue(format, ...) { LogError( "%s" format, ERROR_CONTINUE_PREFIX, ##__VA_ARGS__ ); }

//
// @brief this macro originates the error. Functions down the stack should use
//        @see ContinueErrorEx() or @see ContinueError() to propagate the error.
//
//        In the log it will look like:
//
//        Error: example.c:35 (my_function) - [0000001b] custom error
//         ----> someFile.c:50 (process) - [0000001b]
//         ----> main.c:163 (main) - [00000001]
//
// @param result the value which needs to be logged
// @param resultSpecifier printf() specifier for the result. Ex. "%d" means @c result is of type @c int
//        you can also use "0x%08x" to make it Hex
// @param format, ... - custom formatted message
//
#define OriginateErrorEx(result, resultSpecifier, format, ...) \
    { LogErrorExInit("[" resultSpecifier "] " format, result, ##__VA_ARGS__); return result; }

//
// @see OriginateErrorEx
//
#define OriginateError(result, resultSpecifier) \
    { LogErrorExInit("[" resultSpecifier "] ", result); return result; }

//
// @see OriginateErrorEx
//
#define ContinueErrorEx(result, resultSpecifier, format, ...) \
    { LogErrorExContinue( "[" resultSpecifier "] " format, result, ##__VA_ARGS__ ); return result; }

//
// @see OriginateErrorEx
//
#define ContinueError(result, resultSpecifier) \
    { LogErrorExContinue( "[" resultSpecifier "] ", result ); return result; }

//
// @brief operates the same as @see ContinueErrorEx, but doesn't return
//
#define IgnoreErrorEx(result, resultSpecifier, format, ...) \
    { LogErrorExContinue( "[" resultSpecifier "] " format, result, ##__VA_ARGS__); }

//
// @brief operates the same as @see ContinueError, but doesn't return
//
#define IgnoreError(result, resultSpecifier) \
    { LogErrorExContinue( "[" resultSpecifier "] ", result); }

#endif

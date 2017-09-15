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

#include <stdarg.h>

#include "logger.h"

#define BACKTICK_STR_BUFFER_SIZE 256

const char* LogLevelStr[LL_ERROR + 1] = {
    " DEBUG ",
    " INFO  ",
    "WARNING",
    " ERROR "
};

void *__logData = NULL;
void (*__vlogFunc)(void *data, enum LogLevel logLevel, const char* file, int line, const char* func, const char *format, va_list argp) = NULL;

void logger_log(void *data, enum LogLevel logLevel, const char* file, int line, const char* func, const char *format, ...) {
#ifdef PARAM_CHECKS
    if(__vlogFunc == NULL) {
        return;
    }
#endif
    va_list argp;
    va_start(argp, format);
    __vlogFunc(data, logLevel, file, line, func, format, argp);
    va_end(argp);
}

void logger_vstream(void *data, enum LogLevel logLevel, const char* file, int line, const char* func, const char *format, va_list argp) {
    struct logger_streamData *dt = data;

    if(logLevel < LL_DEBUG) {
        logLevel = LL_DEBUG;
    } else if(logLevel > LL_ERROR) {
        logLevel = LL_ERROR;
    }

    if(logLevel < dt->logLevel) {
        return;
    }

    FILE *stream = (logLevel > LL_INFO)
        ? dt->errStream
        : dt->outStream;

    Bool mod = FALSE;
    for(const char *pch = dt->format; *pch; ++pch) {
        char ch = *pch;

        if(mod) {
            mod = FALSE;

            // is backtick?
            if(ch >= '0' && ch <= '9') {
                size_t index = ch - '0';

                if(index < countof(dt->backtics) && dt->backtics[index]) {
                    char str[BACKTICK_STR_BUFFER_SIZE] = {0};
                    int res = dt->backtics[index](data, str, countof(str));
                    if(res) {
                        fprintf(stream, "~ backtick %zu failed with %d ~", index, res);
                    } else {
                        fputs(str, stream);
                    }
                } else {
                    fprintf(stream, "~ backtick %zu does not exist ~", index);
                }
            } else {
                switch(ch) {
                    case 'm':
                        vfprintf(stream, format, argp);
                        break;
                    case 'L':
                        fputs(LogLevelStr[logLevel], stream);
                        break;
                    case 'F':
                        fputs(file, stream);
                        break;
                    case 'l':
                        fprintf(stream, "%d", line);
                        break;
                    case 'f':
                        fputs(func, stream);
                        break;
                    default:
                        fputc(ch, stream);
                }
            }
        } else if(ch == '%') {
            mod = TRUE;
        } else {
            fputc(ch, stream);
        }
    }

    fputc('\n', stream);
}

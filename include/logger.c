#include <stdarg.h>

#include "logger.h"

#define BACKTICK_STR_BUFFER_SIZE 50

const char* LogLevelStr[LL_ERROR + 1] = {
    " DEBUG ",
    " INFO  ",
    "WARNING",
    " ERROR "
};

void *__logData = NULL;
void (*__logFunc)(void *data, enum LogLevel logLevel, const char* file, int line, const char* func, const char *format, ...) = NULL;

void logger_stream(void *data, enum LogLevel logLevel, const char* file, int line, const char* func, const char *format, ...) {
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
                    int res = dt->backtics[index](str, countof(str));
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
                    case 'm': {
                        va_list args;
                        va_start(args, format);
                        vfprintf(stream, format, args);
                        va_end(args);
                        break;
                    }
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

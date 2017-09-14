#include <stdarg.h>

#include "logger.h"

const char* LogLevelStr[LL_ERROR + 1] = {
    " DEBUG ",
    " INFO  ",
    "WARNING",
    " ERROR "
};

void *__logData = NULL;
void (*__logFunc)(void *data, enum LogLevel logLevel, const char* file, int line, const char* func, const char *format, ...) = NULL;

void logger_simple(void *data, enum LogLevel logLevel, const char* file, int line, const char* func, const char *format, ...) {
    struct logger_simpleData *dt = data;

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

    fprintf(stream, "[%s] %s:%d (%s) - ", LogLevelStr[logLevel], file, line, func);

    va_list args;
    va_start(args, format);
    vfprintf(stream, format, args);
    va_end(args);

    fputc('\n', stream);
}

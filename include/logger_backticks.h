#ifndef LOGGER_BACKTICS_H
#define LOGGER_BACKTICS_H

#include <logger.h>

#ifdef __cplusplus
extern "C" {
#endif

int logger_backtick_time(struct logger_streamData *logData, char *outStr, size_t sz);

#ifdef __cplusplus
}
#endif

#endif

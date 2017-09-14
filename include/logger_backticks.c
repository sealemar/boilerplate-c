#include <time.h>
#include <sys/time.h>
#include <stdio.h>

#include "logger_backticks.h"

int logger_backtick_time(struct logger_streamData *logData, char *outStr, size_t sz) {
    (void)logData;

    struct timeval tv;
    int res = gettimeofday(&tv, NULL);
    if(res) {
        return -1;
    }

    struct tm ts;
    localtime_r( &tv.tv_sec, &ts );

    size_t count = strftime(outStr, sz, "%Y-%m-%d %H:%M:%S", &ts);
    if(count == 0 || count > sz) {
        return -2;
    }

    res = snprintf(outStr + count, sz - count, ".%03d", tv.tv_usec / 1000);
    if(res <= 0) {
        return -3;
    }

    return 0;
}

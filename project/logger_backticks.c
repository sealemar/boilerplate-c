#include <time.h>
#include <sys/time.h>
#include <stdio.h>

#include "logger_backticks.h"

int logger_backtick_time(char *outStr, size_t len) {
    struct timeval tv;
    CallNE(gettimeofday(&tv, NULL));

    struct tm ts;
    localtime_r( &tv.tv_sec, &ts );

    size_t count = strftime(outStr, len, "%Y-%m-%d %H:%M:%S", &ts);
    if(count == 0 || count > len) {
        return -1;
    }

    int res = snprintf(outStr + count, len - count, ".%d", tv.tv_usec);
    if(res <= 0) {
        return -2;
    }

    return 0;
}

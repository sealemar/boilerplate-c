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
// @brief logger backticks
//

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

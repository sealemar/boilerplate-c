// Copyright [2013] [Sergey Markelov]
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
// developed by Sergey Markelov (11/10/2013)
//
// @brief BinaryClock emulator (console, uses ncurses)
//

#include <stdlib.h>
#include <libmain.h>

#include <logger.h>

#include "logger_backticks.h"

// For logger.h
// FILE *errStream;
// FILE *outStream;

int main()
{
//     errStream = stderr;
//     outStream = stdout;
//

    struct logger_streamData loggerData = {
        .errStream = stderr,
        .outStream = stdout,
        .logLevel  = LL_DEBUG,
        .format    = "[%L] %0 - %F:%l (%f) - %m",
        .backtics  = { logger_backtick_time }
    };

    __logData = &loggerData;
    __logFunc = logger_stream;

    mlog(LL_INFO, "start");

    //Call(emulator_init());
    int result = libmain_add(5, 6);
    mlog(LL_DEBUG, "a + b = %d", result);

    mlog(LL_INFO, "end");

    return 0;
}

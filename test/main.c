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
// @brief TestUT framework
//
// developed by Sergey Markelov (09/14/2017)
//

#include <logger/logger_backticks.h>

#include "ut_libmain.h"

FILE *errStream;
FILE *outStream;

static TestUnit testSuites[] = {
    TEST_CASE(ut_libmain, "ut_libmain"),
};

int main()
{
    struct logger_streamData loggerData = {
        .errStream = stderr,
        .outStream = stdout,
        .logLevel  = LL_DEBUG,
        .format    = "[%L] %0 - %F:%l (%f) - %m",
        .backtics  = { logger_backtick_time }
    };

    logger_installStream(&loggerData);

    return runTestSuite(testSuites);
}

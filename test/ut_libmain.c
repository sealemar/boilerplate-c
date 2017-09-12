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
// @brief BinaryClock lib/clock unit tests
//
// developed by Sergey Markelov (11/10/2013)
//

#include <libmain.h>

#include "ut_libmain.h"

static int test_limain_add_correct()
{
    int a = 5, b = 6;
    int result = libmain_add(a, b);

    assert_int(result, a + b);
//    assert_int(result, a + b + 1);

    return 0;
}

static TestUnit testSuite[] = {
    TEST_CASE(test_limain_add_correct, "libmain_add() returns correct result"),
};

int ut_libmain()
{
    return runTestSuite(testSuite);
}

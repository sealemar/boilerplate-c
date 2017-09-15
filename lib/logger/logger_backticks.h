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

#ifndef LOGGER_BACKTICS_H
#define LOGGER_BACKTICS_H

#include "logger.h"

#ifdef __cplusplus
extern "C" {
#endif

int logger_backtick_time(struct logger_streamData *logData, char *outStr, size_t sz);

#ifdef __cplusplus
}
#endif

#endif

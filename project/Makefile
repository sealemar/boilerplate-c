# Copyright [2017] [Sergey Markelov]
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# developed by Sergey Markelov (09/14/2017)
#

# call with DEBUG=1 to make 'debug', otherwise 'release' is made

include ../include/Makefile.project

# for localtime_r() on Linux
MACROS      := -D _BSD_SOURCE

PROG        := $(PROJECT_NAME)
#LIBS         = -lncurses
CTAGS_FILE  := ../etc/project.tags
CTAGS_DIR   := ../project

include ../include/Makefile.include

$(BIN_DIR)/$(PROG): lib

lib:
	$(MAKE) -C ../lib DEBUG=$(DEBUG)

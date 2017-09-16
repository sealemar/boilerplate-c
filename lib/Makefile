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

include ../include/Makefile.project

CTAGS_FILE     := ../etc/lib.tags
CTAGS_DIR      := ../lib

ifndef MAKELIB

define librecipe
    @for libname in `find ../lib -type d -d 1 -exec basename '{}' \;` ; do \
        echo $(MAKE) $1 DEBUG=$(DEBUG) MAKELIB=$${libname} ; \
        $(MAKE) $1 DEBUG=$(DEBUG) MAKELIB=$${libname} ; \
    done
endef

all:
	$(call librecipe)

mostlyclean:
	$(call librecipe,mostlyclean)

clean:
	$(call librecipe,clean)

distclean:
	$(call librecipe,distclean)

include ../include/Makefile.postinclude

else

PROG           := lib$(MAKELIB).a
SOURCE_DIRS_EXCLUDE_DOT := 1
SOURCES_DIRS   := $(MAKELIB)
BUILD_DIR      := $(MAKELIB)/build
USE_GENERIC_CC := 0

include ../include/Makefile.include

$(BIN_DIR)/$(PROG): $(OBJECTS)
	$(AR) rvs $@ $?

endif

# Copyright [2013] [Sergey Markelov]
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
# developed by Sergey Markelov (11/10/2013)
#

.PHONY: all project check clean ctags distclean

all: project

project:
	make -C project

check:
	make -C test && test/build/bin/tests

ctags:
	make -C include -f Makefile.include ctags
	make -C project ctags
	make -C test ctags
	make -C lib ctags

clean:
	make -C project clean
	make -C test clean
	make -C lib clean
	make -C include -f Makefile.include clean

distclean:
	make -C project distclean
	make -C test distclean
	make -C lib distclean
	make -C include -f Makefile.include distclean

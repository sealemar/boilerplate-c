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

.PHONY: all project project-dbg project-debug check test check-dbg test-dbg clean distclean mostlyclean ctags

all: project

project-dbg:
	$(MAKE) -C project dbg

project-debug:
	$(MAKE) -C project DEBUG=1

project:
	$(MAKE) -C project

test check:
	$(MAKE) -C test && test/build/debug/bin/tests

test-dbg check-dbg:
	$(MAKE) -C test dbg

ctags:
	$(MAKE) -C project ctags
	$(MAKE) -C test ctags
	$(MAKE) -C lib ctags

mostlyclean:
	$(MAKE) -C project mostlyclean
	$(MAKE) -C test mostlyclean
	$(MAKE) -C lib mostlyclean

clean:
	$(MAKE) -C project clean
	$(MAKE) -C test clean
	$(MAKE) -C lib clean

distclean:
	$(MAKE) -C project distclean
	$(MAKE) -C test distclean
	$(MAKE) -C lib distclean

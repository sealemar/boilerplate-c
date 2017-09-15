" Copyright [2017] [Sergey Markelov]
"
" Licensed under the Apache License, Version 2.0 (the "License");
" you may not use this file except in compliance with the License.
" You may obtain a copy of the License at
"
"     http://www.apache.org/licenses/LICENSE-2.0
"
" Unless required by applicable law or agreed to in writing, software
" distributed under the License is distributed on an "AS IS" BASIS,
" WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
" See the License for the specific language governing permissions and
" limitations under the License.
"
" developed by Sergey Markelov (09/14/2017)
"

let s:projectDir = expand('<sfile>:p:h')

command! -nargs=1 Silent
\   execute 'silent !' . <q-args>
\ | execute 'redraw!'

"
" Per language setup
"
function! s:initC(type)
"    setlocal notagrelative
"    setlocal tags+=$HOME/.cache/vim-specific/tags/c-home-include
    execute "setlocal path+=" . s:projectDir . "/include"
    execute "setlocal path+=" . s:projectDir . "/lib"

    execute "setlocal tags+=" . s:projectDir . "/etc/tags"

    if a:type == 'project'
        execute "setlocal path+=" . s:projectDir . "/project"
        execute "setlocal tags+=" . s:projectDir . "/etc/project.tags"
        execute "setlocal tags+=" . s:projectDir . "/etc/lib.tags"
    elseif a:type == 'test'
        execute "setlocal path+=" . s:projectDir . "/test"
        execute "setlocal tags+=" . s:projectDir . "/etc/test.tags"
        execute "setlocal tags+=" . s:projectDir . "/etc/lib.tags"
    elseif a:type == 'lib'
        execute "setlocal path+=" . s:projectDir . "/lib"
        execute "setlocal tags+=" . s:projectDir . "/etc/lib.tags"
    endif
endfunction

execute "autocmd BufEnter " . s:projectDir . "/project/*.[ch] call <SID>initC('project')"
execute "autocmd BufEnter " . s:projectDir . "/test/*.[ch] call <SID>initC('test')"
execute "autocmd BufEnter " . s:projectDir . "/lib/*/*.[ch] call <SID>initC('lib')"
execute "autocmd BufEnter " . s:projectDir . "/include/*.[ch] call <SID>initC('')"

"
" Ctags files rebuild
"
execute "autocmd BufWritePost " . s:projectDir . "/project/*.[ch] Silent make -C " . s:projectDir . "/project ctags"
execute "autocmd BufWritePost " . s:projectDir . "/test/*.[ch] Silent make -C " . s:projectDir . "/test ctags"
execute "autocmd BufWritePost " . s:projectDir . "/lib/*/*.[ch] Silent make -C " . s:projectDir . "/lib ctags"
execute "autocmd BufWritePost " . s:projectDir . "/include/*.[ch] Silent make -C " . s:projectDir . "/include ctags"

"
" Session managemenr
"
function! s:saveSession()
    execute "Silent mkdir -p " . s:projectDir . "/etc"
    if filereadable(s:sessionFile)
        execute "Silent mv " . s:sessionFile . " " . s:sessionOldFile
    endif
    execute "mksession " . s:sessionFile
endfunction

function! s:restoreSession()
    if filereadable(s:sessionFile)
        execute "source " .s:sessionFile
    endif
endfunction

set sessionoptions=buffers,curdir,folds,globals,help,localoptions,options,resize,slash,tabpages,unix,winpos,winsize
let s:sessionFile = s:projectDir . '/etc/Session.vim'
let s:sessionOldFile = s:projectDir . '/etc/Session.old.vim'
autocmd VimLeave * call <SID>saveSession()
autocmd VimEnter * call <SID>restoreSession()

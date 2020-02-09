" activates filetype detection
filetype plugin indent on

" activates syntax highlighting among other things
syntax on

" allows you to deal with multiple unsaved
" buffers simultaneously without resorting
" to misusing tabs
set hidden

set backspace=indent,eol,start

set tabstop=4
set shiftwidth=4
set expandtab

" line numbers and their highlighting
set number
highlight LineNr cterm=italic ctermfg=DarkGrey ctermbg=NONE
set cursorline
highlight CursorLine cterm=NONE
highlight CursorLineNr cterm=bold ctermfg=White ctermbg=NONE

let localleader = "\\"
let g:vimtex_view_general_viewer = "zathura"
let g:vimtex_quickfix_open_on_warning = 0
""""""""""""""""""""""""""""""""""""""""""""
" call plug#begin('~/.vim/plugged')
" Plug 'lervag/vimtex'
" call plug#end()


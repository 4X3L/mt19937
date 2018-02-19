project('mt19937', 'c', default_options : 'c_std=c99')
c_flags = ['-Wall', '-Wextra', '-Werror', '-O3']
src = 'mt.c'
install_headers('mt.h')
shared_library('mt19937', src, c_args : c_flags, install : true)
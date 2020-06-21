# © Richard Kettewell. See README.md for more info.
tag:=$(shell git describe --tags --dirty --always)

bin_PROGRAMS=rot13
rot13_SOURCES=rot13.h rot13.c

noinst_PROGRAMS=test_rot13
test_rot13_SOURCES=test_rot13.c rot13.h
TESTS=test_rot13

AM_CPPFLAGS=-D_GNU_SOURCE=1 -DTAG=\"${tag}\"
man_MANS=rot13.1
EXTRA_DIST=${man_MANS} README.md .clang-format .gitignore
ACLOCAL_AMFLAGS=-I m4

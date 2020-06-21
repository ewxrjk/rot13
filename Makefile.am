#
# This file is part of rot13.
# Copyright © Richard Kettlewell
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
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

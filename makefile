## INFO ########################################################################
##                                                                            ##
##                                  pycasso                                   ##
##                                  =======                                   ##
##                                                                            ##
##    Cross-platform, hardware accelerated, constraint based GUI framework    ##
##                       Version: 0.5.02.035 (20140911)                       ##
##                                                                            ##
##                               File: makefile                               ##
##                                                                            ##
##  For more information about the project, visit <http://www.pycasso.org>.   ##
##                       Copyright (C) 2014 Peter Varo                        ##
##                                                                            ##
##  This program is free software: you can redistribute it and/or modify it   ##
##   under the terms of the GNU General Public License as published by the    ##
##       Free Software Foundation, either version 3 of the License, or        ##
##                    (at your option) any later version.                     ##
##                                                                            ##
##    This program is distributed in the hope that it will be useful, but     ##
##         WITHOUT ANY WARRANTY; without even the implied warranty of         ##
##            MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.            ##
##            See the GNU General Public License for more details.            ##
##                                                                            ##
##     You should have received a copy of the GNU General Public License      ##
##     along with this program, most likely a file in the root directory,     ##
##        called 'LICENSE'. If not, see <http://www.gnu.org/licenses>.        ##
##                                                                            ##
######################################################################## INFO ##

#------------------------------------------------------------------------------#
# User flags
IS_OPTIMISED=
USE_JEMALLOC=
EXCEPTION_LOG=true
DYNAMIC_LIB=

# Location 'prefix'
LOCATION=/usr/local

# Locations
INCLUDE_FOLDER=$(LOCATION)/include
LIBRARY_FOLDER=$(LOCATION)/lib
BINARY_FOLDER=$(LOCATION)/bin
PYTHON=$(LOCATION)/bin/python3

# Compiler
CC=clang
#------------------------------------------------------------------------------#

# Filename of library
pycasso_NAME=libpycasso

# Output dirs
# TODO: rename folders:
#		src     -> source
#       include -> header
pycasso_SOURCE_IN_DIR=src
pycasso_HEADER_IN_DIR=include
pycasso_BUILD_OUT_DIR=build
pycasso_BUILD_TMP_DIR=$(pycasso_BUILD_OUT_DIR)/tmp

# Resources in current library
pycasso_C_SOURCES=$(addprefix $(pycasso_SOURCE_IN_DIR)/, session.c window.c \
					shader/helper.c shader/program.c shader/resources.c \
					geo/rectangle.c)
#$(wildcard *.c)
pycasso_C_OBJECTS=$(addprefix $(pycasso_BUILD_TMP_DIR)/, $(notdir $(pycasso_C_SOURCES:.c=.o)))

# TODO: collect publuc headers only to copy them directly to /usr/*/pycasso
pycasso_H_SOURCES=$(addprefix $(pycasso_HEADER_IN_DIR)/, session.h window.h \
					shader/helper.h shader/program.h shader/resources.h \
					geo/rectangle.h)
#$(wildcard include/*.h)

# Includes, libs and frameworks
pycasso_INCLUDE_DIRS=/usr/local/include .
pycasso_LIBRARY_DIRS=/usr/local/lib
pycasso_LIBRARIES=jemalloc cutils glfw3 GLEW
pycasso_FRAMEWORKS=Cocoa OpenGL IOKit CoreVideo

# Resources: shaders
# pycasso_V_SHADERS=$(wildcard shaders/vertex/*.vs)
# pycasso_F_SHADERS=$(wildcard shaders/fragment/*.fs)

# If use the jemalloc library
ifdef USE_JEMALLOC
pycasso_LIBRARIES+=jemalloc
CFLAGS+=$(addprefix -D, CDAR_JEM CSLL_JEM)
endif

# Flags
ifdef IS_OPTIMISED
CFLAGS+=-O3 $(addprefix -D, CDAR_OPT CSLL_OPT)
else
CFLAGS+=-Wall -v -g
endif

# If compiler is clang
ifeq ($(CC), clang)
CFLAGS+=-fmacro-backtrace-limit=0
endif

ifdef EXCEPTION_LOG
CFLAGS+=-D CEXC_LOG
endif

CFLAGS+=-std=c11 $(addprefix -I, $(pycasso_INCLUDE_DIRS))
CFLAGS+=$(foreach framework, $(pycasso_FRAMEWORKS), -framework $(framework))
LDFLAGS=$(addprefix -L, $(pycasso_LIBRARY_DIRS))
LDFLAGS+=$(addprefix -l, $(pycasso_LIBRARIES))

# Rules
.PHONY: all clean install
.PHONY: make_build_dirs make_install_dirs
.PHONY: build_generic build_static

all: make_build_dirs build_generic build_static

$(pycasso_BUILD_TMP_DIR)/%.o: $(pycasso_SOURCE_IN_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(pycasso_BUILD_TMP_DIR)/%.o: $(pycasso_SOURCE_IN_DIR)/shader/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(pycasso_BUILD_TMP_DIR)/%.o: $(pycasso_SOURCE_IN_DIR)/geo/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

build_generic:
	$(PYTHON) dev/proj.py

build_static: $(pycasso_C_OBJECTS)
	ar -c -r -s -v $(pycasso_BUILD_OUT_DIR)/$(pycasso_NAME).a $(pycasso_C_OBJECTS)

# $(pycasso_BUILD_TMP_DIR)/%.o: %.c
# 	$(CC) $(CFLAGS) -fPIC -c -o $@ $<

# build_shared: $(pycasso_NAME)
# 	$(CC) -shared -Wl -soname -o $(pycasso_BUILD_OUT_DIR)/$(pycasso_NAME).so

install: make_install_dirs
	cp -Rf $(pycasso_BUILD_OUT_DIR)/$(pycasso_NAME).a $(LIBRARY_FOLDER)/$(pycasso_NAME).a
	cp -Rf $(pycasso_H_SOURCES) $(INCLUDE_FOLDER)/pycasso

# Create build dir and tmp dir inside it
make_build_dirs:
	mkdir -p $(pycasso_BUILD_TMP_DIR)

make_install_dirs:
	mkdir -p $(INCLUDE_FOLDER)/pycasso

# Remove build dir and all dirs and files inside
clean:
	rm -f -r $(pycasso_BUILD_OUT_DIR)

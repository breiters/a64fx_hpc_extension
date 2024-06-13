SHELL    ?= /bin/sh

CC       := gcc
CFLAGS   := -fPIC -pedantic -Wall -Wextra -march=native -g # -ggdb3
LDFLAGS  := -shared
CPPFLAGS := -Iinclude

DEBUGFLAGS   := -O0 -D _DEBUG
RELEASEFLAGS := -O2 -D NDEBUG -flto # -fwhole-program

CFLAGS += $(RELEASEFLAGS)
# CFLAGS += $(DEBUGFLAGS)

TARGET  := liba64fx_hpc_extension.so
INCLUDE := a64fx_hpc_extension.h

SOURCES := $(wildcard src/*.c)
OBJECTS := $(SOURCES:.c=.o)

PREFIX ?= /usr/

LIBDIR     := $(DESTDIR)$(PREFIX)/lib64
INCLUDEDIR := $(DESTDIR)$(PREFIX)/include

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

install: $(TARGET)
	install -D $(TARGET)          $(LIBDIR)/$(TARGET)
	install -D include/$(INCLUDE) $(INCLUDEDIR)/$(INCLUDE)

.PHONY: clean help

clean:
	$(RM) $(OBJECTS) $(TARGET)

help:
	@echo TODO

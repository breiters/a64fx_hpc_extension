SHELL ?= /bin/sh
CC     = gcc
CFLAGS = -fPIC -pedantic -Wall -Wextra -march=native -g # -ggdb3

LDFLAGS = -shared
CPPFLAGS =

DEBUGFLAGS   = -O0 -D _DEBUG
RELEASEFLAGS = -O2 -D NDEBUG -flto # -fwhole-program

CFLAGS += $(RELEASEFLAGS)

TARGET  = liba64fx_hpc_extension.so
SOURCES = $(wildcard *.c)
# HEADERS = $(shell echo include/*.h)
OBJECTS = $(SOURCES:.c=.o)

# PREFIX = $(DESTDIR)/usr/local
# BINDIR = $(PREFIX)/bin

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

.PHONY: clean
clean:
	$(RM) $(OBJECTS) $(TARGET)

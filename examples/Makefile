INCLUDE := ../lib/include
LIBRARY := ../lib

PWD := $(CURDIR)

CFLAGS   += -fopenmp -Wall -pedantic
CPPFLAGS += -I$(INCLUDE)
LDLIBS   += -la64fx_hpc_extension
LDFLAGS  += -L$(LIBRARY) -Wl,-rpath=$(PWD)/$(LIBRARY)

TARGET := main

all: $(TARGET)

$(TARGET):

.PHONY: clean
clean:
	$(RM) $(TARGET)

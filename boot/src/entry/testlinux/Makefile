# This file must produce entry.o

SOURCES = $(wildcard *.c)
DEPFILES = $(patsubst %.c,%.d,$(SOURCES))
OBJFILES = $(patsubst %.c,%.o,$(SOURCES))
# Not allowed to access libs
INCFLAGS = -I../../../include/arch/$(ARCH) -I../../../include/comp/$(CC)

.PHONY: all build boot clean

all: build

build: boot

boot: $(OBJFILES)

clean:
	rm -rf $(DEPFILES)
	rm -rf $(OBJFILES)
	
include ../../../rules.mk
	
include ../../../depsgrab.mk
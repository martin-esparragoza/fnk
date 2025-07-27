# This makefile is responsible for the compilation of the .c (also the ones in the directory specific tho)

SOURCES = $(wildcard *.c) $(wildcard arch/$(ARCH)/*.c) $(wildcard comp/$(CC)/*.c)

DEPFILES = $(patsubst %.c,%.d,$(SOURCES))
OBJFILES = $(patsubst %.c,%.o,$(SOURCES))

.PHONY: all build clean

all: build

build: $(OBJFILES)

clean:
	rm -rf $(DEPFILES)
	rm -rf $(OBJFILES)

include ../../rules.mk

include ../../depsgrab.mk
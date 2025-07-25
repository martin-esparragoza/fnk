# This makefile is responsible for the compilation of the .c (also the ones in the directory specific tho)

SOURCES = $(wildcard *.c) $(wildcard arch/$(ARCH)/*.c) $(wildcard comp/$(CC)/*.c)

DEPFILES = $(patsubst %.c,%.d,$(SOURCES))
OBJFILES = $(patsubst %.c,%.o,$(SOURCES))

.PHONY: all build boot clean

all: build

# This is going to come up a lot of times. Just treat build as boot so when you do make boot it works
build: boot

# Remember that building objfiles will generate depfiles
boot: $(OBJFILES)

clean:
	rm -rf $(DEPFILES)
	rm -rf $(OBJFILES)

include ../../rules.mk

include ../../depsgrab.h
# We have to get the stuff in lib/ so we can assemble everything here

SOURCES = main.c
DEPFILES = $(patsubst %.c,%.d,$(SOURCES))
OBJFILES = $(patsubst %.c,%.o,$(SOURCES)) entry/$(ARCH)/entry.o
MAKEDIRS = entry/$(ARCH)/

.PHONY: all build clean $(MAKEDIRS)

all: build

build: $(MAKEDIRS) $(OBJFILES)

clean: $(MAKEDIRS)
	rm -rf $(OBJFILES)
	rm -rf $(DEPFILES)
	
entry/$(ARCH)/entry.o: # We want our custom makefile to link this instead (but keep it as a dep)
	@:

include ../../rules.mk

include ../../makedirs.mk

include ../../depsgrab.mk
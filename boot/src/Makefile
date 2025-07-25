# We have to get the stuff in lib/ so we can assemble everything here

SOURCES = main.c entry/$(ARCH)/entry.c
DEPFILES = $(patsubst %.c,%.d,$(SOURCES))
OBJFILES = $(patsubst %.c,%.o,$(SOURCES))
MAKEDIRS = entry/$(ARCH)/

.PHONY: all build boot clean $(MAKEDIRS)

all: build

build: boot

boot: $(MAKEDIRS) $(OBJFILES)

clean: $(MAKEDIRS)
	rm -rf $(OBJFILES)
	rm -rf $(DEPFILES)

include ../../rules.mk
	
entry/$(ARCH)/entry.o: # We want our custom makefile to link this instead (but keep it as a dep)
	@:

include ../../makedirs.h

include ../../depsgrab.mk
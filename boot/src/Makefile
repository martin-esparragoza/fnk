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

OUT: linker_$(ARCH).ld $(OBJFILES)

# Avoid custom linker script until this thing actually has be to used. (It should be linked correctly and freestanding later)
#rtfnk_$(ARCH): linker_$(ARCH).ld $(OBJFILES) $(LIBFILES)
#	$(LD) -T $< -o $@ $(OBJFILES) $(LIBFILES)
	
rtfnk_$(ARCH): linker_$(ARCH).ld $(OBJFILES) $(LIBFILES)
	$(LD) $(LDFLAGS) -o $@ $(OBJFILES) -e entry -Wl,--start-group $(LIBFILES) -Wl,--end-group

include ../../makedirs.h

include ../../depsgrab.mk
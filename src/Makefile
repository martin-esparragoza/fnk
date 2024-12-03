SOURCES = main.c entry/$(ARCH)/entry.c
DEPFILES = $(patsubst %.c,%.d,$(SOURCES))
OBJFILES = $(patsubst %.c,%.o,$(SOURCES))
LIBFILES = $(wildcard ../lib/*.a) ../lib/arch/$(ARCH).a
INCFLAGS = -I../include/arch/$(ARCH) -I../include/comp/$(CC) -I ../
MAKEDIRS = entry/$(ARCH)/

.PHONY: all deps build clean $(MAKEDIRS)

all: build

clean: $(MAKEDIRS)
	rm -rf *.o
	rm -rf rtfnk
	rm -rf *.d

build: deps $(OBJFILES) rtfnk

deps: $(MAKEDIRS) $(DEPFILES)

%.d: %.c
	$(CC) -MM $(INCFLAGS) $< -MF $@
	
%.o: %.c
	$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@ $(CLINK)
	
entry/$(ARCH)/entry.o: # We want our custom makefile to link this instead (but keep it as a dep)
	@:

entry/$(ARCH)/entry.d:
	@:


# Avoid custom linker script until this thing actually has be to used. (It should be linked correctly and freestanding later)
#rtfnk: linker.ld $(OBJFILES) $(LIBFILES)
#	$(LD) -T $< -o $@ $(OBJFILES) $(LIBFILES)
	
rtfnk: linker.ld $(OBJFILES) $(LIBFILES)
	$(LD) -o $@ $(OBJFILES) -e entry $(LIBFILES)


$(MAKEDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

ifneq ($(MAKECMDGOALS),clean)
include $(DEPFILES)
endif
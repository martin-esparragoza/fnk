BINARY := boot/boot_$(ARCH)

SOURCES := $(wildcard boot/lib/*.c)
OBJFILES := $(patsubst %.c,%.o,$(SOURCES))
# Depfiles is nothing because we're effectively resolving our deps ourselves (becuse its the final build)
DEPFILES :=
TARGETS := $(BINARY)

# Yes, we want the objfiles from the upper level make but we don't want make clean to double trigger
# These are always expected to be defined. Constants
UPPEROBJS := boot/src/main.o boot/src/entry/$(ARCH)/entry.o
LIBFILES := arch/$(ARCH).o comp/$(CC).o common/common.o

$(UPPEROBJS) $(LIBFILES) $(OBJFILES):
	@

$(BINARY): boot/linker_$(ARCH).ld $(OBJFILES) $(UPPEROBJS)
#	$(LD) $(LDFLAGS) -o $@ -T $< -Wl,--start-group $(OBJFILES) $(LIBFILES) $(UPPEROBJS) -Wl,--end-group
	$(LD) $(LDFLAGS) -o $@ -Wl,--start-group $(OBJFILES) $(LIBFILES) $(UPPEROBJS) -Wl,--end-group
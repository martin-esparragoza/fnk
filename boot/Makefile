# TODO: Refactor this file for use in not devenv

BINARY := boot/boot_$(ARCH)

SOURCES := $(wildcard boot/lib/*.c)
OBJFILES := $(patsubst %.c,%.o,$(SOURCES))
# Depfiles is nothing because we're effectively resolving our deps ourselves (becuse its the final build)
DEPFILES :=
TARGETS := $(BINARY)

# Yes, we want the objfiles from the upper level make but we don't want make clean to double trigger
# These are always expected to be defined. Constants
UPPEROBJS := boot/src/main.o boot/src/entry/$(ARCH)/entry.o
LIBFILES := arch/lib$(ARCH).o comp/lib$(CC).o common/libcommon.o

$(UPPEROBJS) $(LIBFILES) $(OBJFILES):
	@

$(BINARY): boot/linker_$(ARCH).ld $(OBJFILES) $(UPPEROBJS) $(LIBFILES)
#	$(LD) $(LDFLAGS) -o $@ -T $< -Wl,--start-group $(OBJFILES) $(LIBFILES) $(UPPEROBJS) -Wl,--end-group
# Funky stuff so it can run silly goose
	gcc -o $@ -Wl,--start-group $(OBJFILES) $(LIBFILES) $(UPPEROBJS) -Wl,--end-group
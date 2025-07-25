INCFLAGS = -I../include/arch/$(ARCH) -I -I ../../
export

MAKEDIRS = lib/ src/
OUT = boot_$(ARCH)

SOURCES = $(wildcard lib/*.c) $(wildcard lib/arch/$(ARCH)/*.c) $(wildcard lib/comp/$(CC)/*.c) src/main.c src/entry/$(ARCH)/entry.c
OBJFILES = $(patsubst %.c,%.o,$(SOURCES))

.PHONY: all build boot clean $(MAKEDIRS)

all: build

build: boot

boot: $(MAKEDIRS) $(OUT)

clean: $(MAKEDIRS)

$(OUT): linker_$(ARCH).ld $(OBJFILES)
	$(LD) $(LDFLAGS) -o $@ -T $< -Wl,--start-group $(OBJFILES) -Wl,--end-group
#rtfnk_$(ARCH): linker_$(ARCH).ld $(OBJFILES) $(LIBFILES)
#	$(LD) $(LDFLAGS) -o $@ $(OBJFILES) -e entry -Wl,--start-group $(LIBFILES) -Wl,--end-group

include ../makedirs.mk
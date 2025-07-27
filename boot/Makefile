# A bit misleading bc this is not the current context and instead the subdirectory context
INCFLAGS := -I../../arch/$(ARCH)/include/ -I../../comp/$(CC)/include/ -I ../../
export

SOURCES = $(wildcard lib/*.c) src/main.c
OBJFILES = $(patsubst %.c,%.o,$(SOURCES))

boot_$(ARCH): linked_$(ARCH).ld $(OBJFILES)

MAKEDIRS = lib/ src/

SOURCES = $(wildcard lib/*.c) src/main.c src/entry/$(ARCH)/entry.c
OBJFILES = $(patsubst %.c,%.o,$(SOURCES))
LIBFILES = ../arch/$(ARCH).a ../comp/$(CC).a ../common/common.a

.PHONY: clean $(MAKEDIRS)

all: build

build: $(MAKEDIRS) $(OUT)

clean: $(MAKEDIRS)

$(OUT): linker_$(ARCH).ld $(OBJFILES)
	$(LD) $(LDFLAGS) -o $@ -T $< -Wl,--start-group $(OBJFILES) $(LIBFILES) -Wl,--end-group
#rtfnk_$(ARCH): linker_$(ARCH).ld $(OBJFILES) $(LIBFILES)
#	$(LD) $(LDFLAGS) -o $@ $(OBJFILES) -e entry -Wl,--start-group $(LIBFILES) -Wl,--end-group

# Just for clean
include ../makedirs.mk
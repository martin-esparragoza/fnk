INCFLAGS = -I../include/arch/$(ARCH) -I -I ../../
export

MAKEDIRS = lib/ src/

.PHONY: all build boot clean $(MAKEDIRS)

all: build

build: boot

boot: $(MAKEDIRS)
	# TODO: Package everything together

clean: $(MAKEDIRS)

include ../makedirs.mk
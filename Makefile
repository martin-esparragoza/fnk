# Set this yourself
ARCH = testlinux.a

CC = gcc
AR = ar
CFLAGS = -Wall --freestanding -fPIC
CLINK =
export

MAKEDIRS = lib/ src/

define done
	$(info $(CURDIR): Finished operation $@)
endef

.PHONY: all deps build clean $(MAKEDIRS)

all: build
	$(call done)

clean: $(MAKEDIRS)
	$(call done)

build: deps
	$(call done)

deps: $(MAKEDIRS)
	$(call done)

$(MAKEDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

# Set this yourself
ARCH = testlinux.a

CC = gcc
AR = ar
CFLAGS = -Wall --freestanding
CLINK =
export

MAKEDIRS = lib/ src/

.PHONY: all deps build clean $(MAKEDIRS)

all: build

clean: $(MAKEDIRS)

build: deps

deps: $(MAKEDIRS)

$(MAKEDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

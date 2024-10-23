# Set this yourself
ARCH = testlinux

CC = gcc
AR = ar
CFLAGS = -Wall --freestanding -std=c99
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

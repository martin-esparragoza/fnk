# Set this yourself
ARCH = testlinux

AR = ar
ARFLAGS =

# Im using gcc here just because some stdc stuff is used for now
LD = gcc
LDFLAGS =

CC = gcc
CFLAGS = -Wall -ffreestanding -std=c99 -fno-stack-protector -flto
CLINK =
export

MAKEDIRS = lib/ src/

.PHONY: all deps build clean docs $(MAKEDIRS)

all: build

clean: $(MAKEDIRS)
	rm -rf man/

build: deps

deps: $(MAKEDIRS)

$(MAKEDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

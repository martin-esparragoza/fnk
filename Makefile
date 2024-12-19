# Set this yourself
ARCH = testlinux

CC = gcc
AR = ar
# Im using gcc here just because some stdc stuff is used for now
LD = gcc
CFLAGS = -Wall --freestanding -std=c99 -fno-stack-protector
CLINK =
export

MAKEDIRS = lib/ src/

.PHONY: all deps build clean docs $(MAKEDIRS)

all: build

clean: $(MAKEDIRS)
	rm -rf man/

build: deps

docs:
	@doxygen

deps: $(MAKEDIRS)

$(MAKEDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

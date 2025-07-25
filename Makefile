# Set this yourself
ARCH = testlinux

LD = ld
LDFLAGS =

CC = gcc
CFLAGS = -Wall -ffreestanding -std=c99 -fno-stack-protector -flto
CLINK =
export

MAKEDIRS = boot/ dll/ kernel/

.PHONY: all build boot dll kernel clean $(MAKEDIRS)

boot: boot/

dll: dll/

kernel: kernel/

all: build
# TODO: assemble all of them together

build: boot/ dll/ kernel/

clean: $(MAKEDIRS)

include makedirs.mk
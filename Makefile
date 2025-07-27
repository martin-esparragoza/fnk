# Set this yourself
ARCH = testlinux

LD = ld
LDFLAGS =

CC = gcc
CFLAGS = -Wall -ffreestanding -std=c99 -fno-stack-protector -flto
CLINK =

export

MAKEDIRS = arch/ comp/ common/ boot/
# TODO: add dll/ and kernel/

.PHONY: all build clean $(MAKEDIRS)

all: build
# TODO: assemble all of them together

build clean: $(MAKEDIRS) 

include makedirs.mk
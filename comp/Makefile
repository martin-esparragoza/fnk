# I'd really not like to add more abstraction to the build system than necessary.. So this is coppied..
SOURCES = $(wildcard $(CC)/lib/*.c)

DEPFILES = $(patsubst %.c,%.d,$(SOURCES))
OBJFILES = $(patsubst %.c,%.o,$(SOURCES))
INCFLAGS = -I ../ -I ../arch/$(ARCH)/include/

.PHONY: all build clean

all: build

build: $(CC).o
	
clean:
	rm -rf $(DEPFILES)
	rm -rf $(OBJFILES)
	
$(CC).o: $(OBJFILES)
	$(LD) $(LDFLAGS) -r -o $@ $^

include ../rules.mk

include ../depsgrab.mk
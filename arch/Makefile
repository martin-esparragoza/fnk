SOURCES = $(wildcard $(ARCH)/lib/*.c)

DEPFILES = $(patsubst %.c,%.d,$(SOURCES))
OBJFILES = $(patsubst %.c,%.o,$(SOURCES))
INCFLAGS = -I ../ -I ../comp/$(CC)/include/

.PHONY: all build clean

all: build

build: $(ARCH).o
	
clean:
	rm -rf $(DEPFILES)
	rm -rf $(OBJFILES)
	
$(ARCH).o: $(OBJFILES)
	$(LD) $(LDFLAGS) -r -o $@ $^

include ../rules.mk

include ../depsgrab.mk
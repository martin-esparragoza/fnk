DEPFILES = $(patsubst %.c,%.d,$(wildcard *.c))
OBJFILES = $(patsubst %.c,%.o,$(wildcard *.c))
LIBFILES = $(wildcard ../lib/*.a) ../lib/arch/$(ARCH)

.PHONY: all deps build clean

all: build
	@echo $(LIBFILES)

clean:
	rm -rf *.o
	rm -rf *.d

build: deps $(OBJFILES)

deps: $(DEPFILES)

%.d: %.c
	$(CC) -MM $< -MF $@

%.o: %.c $(LIBFILES)
	$(CC) $(CFLAGS) $< -o $@ $(CLINK) $(LIBFILES)

ifneq ($(MAKECMDGOALS),clean)
include $(DEPFILES)
endif

DEPFILES = $(patsubst %.c,%.d,$(wildcard *.c))
OBJFILES = $(patsubst %.c,%.o,$(wildcard *.c))
LIBFILES = $(wildcard ../lib/*.a) ../lib/arch/$(ARCH).a
INCFLAGS = -I../include/arch/$(ARCH) -I ../include/comp/$(CC) -I ../

.PHONY: all deps build clean

all: build

clean:
	rm -rf *.o
	rm -rf *.d

build: deps $(OBJFILES)

deps: $(DEPFILES)

%.d: %.c
	$(CC) -MM $(INCFLAGS) $< -MF $@

%.o: %.c $(LIBFILES)
	$(CC) $(CFLAGS) $(INCFLAGS) $< -o $@ $(CLINK) $(LIBFILES)

ifneq ($(MAKECMDGOALS),clean)
include $(DEPFILES)
endif

# This makefile is responsible for the compilation of all libraries (situated in folders)

MAKEDIRS = rtfnk $(wildcard arch/*/) drivers
DEPFILES = $(patsubst %.c,%.d,$(wildcard */*.c))
OBJFILES = $(patsubst %.c,%.o,$(wildcard */*.c))
LIBFILES = $(MAKEDIRS:=.a)

.PHONY: all deps build clean

all: build

clean:
	rm -rf $(MAKEDIRS:=/*.o)
	rm -rf $(MAKEDIRS:=/*.d)
	rm -rf *.a

build: deps $(LIBFILES)

deps: $(DEPFILES)

%.d: %.c
	$(CC) -MM $< -MF $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(CLINK)

%.a: $(OBJFILES)
	$(AR) cr $@ $^ $(filter $^,$@/%.o)

ifneq ($(MAKECMDGOALS),clean)
include $(DEPFILES)
endif

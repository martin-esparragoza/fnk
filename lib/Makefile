# This makefile is responsible for the compilation of all libraries (situated in folders)

MAKEDIRS = rtfnk/ $(wildcard arch/*/) sdrive/ util/
$(eval MAKEDIRS = $(filter %/,$(MAKEDIRS)))
DEPFILES = $(patsubst %.c,%.d,$(wildcard */*.c))
OBJFILES = $(patsubst %.c,%.o,$(wildcard */*.c) $(wildcard arch/*/*.c))
LIBFILES = $(patsubst %/,%.a,$(MAKEDIRS))

.PHONY: all deps build clean

all: build

clean:
	rm -rf $(MAKEDIRS:=*.o)
	rm -rf $(MAKEDIRS:=*.d)
	rm -rf arch/*.a
	rm -rf *.a

build: deps $(OBJFILES) $(LIBFILES)

deps: $(DEPFILES)

# You may be asking why the -I . is there. It is so the deps can be relative to lib/ when we do the deps check
# (its because of subdirs)

%.d: %.c
	$(CC) -MM -I . $< -MF $@

%.o: %.c
	$(CC) $(CFLAGS) -I . -c $< -o $@ $(CLINK)

%.a: $(OBJFILES)
	$(eval DIR = $(patsubst %.a,%,$@))
	$(AR) cr $@ $(filter $(DIR)/%.o,$^)

ifneq ($(MAKECMDGOALS),clean)
include $(DEPFILES)
endif

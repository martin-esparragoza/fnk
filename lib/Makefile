# This makefile is responsible for the compilation of all libraries (situated in folders)

MAKEDIRS = rtfnk/ arch/$(ARCH) sdrive/ util/ comp/$(CC)
$(eval MAKEDIRS = $(filter %/,$(MAKEDIRS)))
DEPFILES = $(patsubst %.c,%.d,$(wildcard */*.c))
OBJFILES = $(patsubst %.c,%.o,$(wildcard */*.c) $(wildcard arch/$(ARCH)/*.c))
LIBFILES = $(patsubst %/,%.a,$(MAKEDIRS))
INCFLAGS = -I ../include/arch/$(ARCH) -I ../include/comp/$(CC) -I ../

.PHONY: all deps build clean

all: build

clean:
	rm -rf $(MAKEDIRS:=*.o)
	rm -rf $(MAKEDIRS:=*.d)
	rm -rf arch/$(ARCH)/*.a
	rm -rf *.a

build: deps $(OBJFILES) $(LIBFILES)

deps: $(DEPFILES)
	
# Yeah idk why deps sometimes doesnt work

%.d: %.c
	$(CC) -MM $(INCFLAGS) $< -MF $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@ $(CLINK)

%.a: $(OBJFILES)
	$(eval DIR = $(patsubst %.a,%,$@))
	$(AR) cr $@ $(filter $(DIR)/%.o,$^)
	
ifneq ($(MAKECMDGOALS),clean)
include $(DEPFILES)
endif
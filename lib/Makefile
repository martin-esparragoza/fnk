# This makefile is responsible for the compilation of all libraries (situated in folders)

MAKEDIRS = rtfnk/ arch/$(ARCH)/ sdrive/ util/ comp/$(CC)/ mem/
$(eval MAKEDIRS = $(filter %/,$(MAKEDIRS))) # Future martin here. Why does this exist?
SOURCES = $(wildcard */*.c) $(wildcard arch/$(ARCH)/*.c $(wildcard comp/$(CC)/*.c))

DEPFILES = $(patsubst %.c,%.d,$(SOURCES))
OBJFILES = $(patsubst %.c,%.o,$(SOURCES))
LIBFILES = $(patsubst %/,%.a,$(MAKEDIRS))
INCFLAGS = -I ../include/arch/$(ARCH) -I ../include/comp/$(CC) -I ../

.PHONY: all build clean

all: build

clean:
	rm -rf $(MAKEDIRS:=*.o)
	rm -rf $(MAKEDIRS:=*.d)
	rm -rf arch/$(ARCH)/*.a
	rm -rf *.a

build: $(OBJFILES) $(LIBFILES)

%.o: %.c
	$(CC) $(CFLAGS) -MMD -MP $(INCFLAGS) -c $< -o $@ $(CLINK)

%.a: $(OBJFILES)
	$(eval DIR = $(patsubst %.a,%,$@))
	$(AR) $(ARFLAGS) cr $@ $(filter $(DIR)/%.o,$^)
	
ifneq ($(MAKECMDGOALS),clean)
-include $(DEPFILES)
endif
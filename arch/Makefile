LIB := arch/$(ARCH).o
SOURCES := $(wildcard arch/$(ARCH)/lib/*.c)
OBJFILES := $(patsubst %.c,%.o,$(SOURCES))
DEPFILES := $(patsubst %.c,%.d,$(SOURCES))
$(LIB): $(OBJFILES)
	$(LD) $(LDFLAGS) -r -o $@ $^
TARGETS := $(LIB)
LIB := arch/$(ARCH).o
SOURCES := $(wildcard arch/$(ARCH)/lib/*.c)
OBJFILES := $(wildcard %.c,%.o,$(SOURCES))
TARGETS := $(OBJFILES) $(LIB)
DEPFILES := $(patsubst %.c,%.d,$(SOURCES))
$(LIB): $(OBJFILES)
	$(LD) $(LDFLAGS) -r -o $@ $^
LIB := common/common.o
SOURCES := $(wildcard common/lib/*.c)
OBJFILES := $(patsubst %.c,%.o,$(SOURCES))
TARGETS := $(OBJFILES) $(LIB)
DEPFILES := $(patsubst %.c,%.d,$(SOURCES))
$(LIB): $(OBJFILES)
	$(LD) $(LDFLAGS) -r -o $@ $^
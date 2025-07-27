LIB := common/common.o
SOURCES := $(wildcard common/lib/*.c)
OBJFILES := $(patsubst %.c,%.o,$(SOURCES))
DEPFILES := $(patsubst %.c,%.d,$(SOURCES))
$(LIB): $(OBJFILES)
	$(LD) $(LDFLAGS) -r -o $@ $^
TARGETS := $(LIB)
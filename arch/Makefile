LIB := arch/lib$(ARCH).o
SOURCES := $(wildcard arch/$(ARCH)/lib/*.c)
OBJFILES := $(patsubst %.c,%.o,$(SOURCES))
TARGETS := $(OBJFILES) $(LIB)
DEPFILES := $(patsubst %.c,%.d,$(SOURCES))
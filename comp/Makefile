LIB := comp/lib$(CC).o
SOURCES := $(wildcard comp/$(CC)/lib/*.c)
OBJFILES := $(patsubst %.c,%.o,$(SOURCES))
TARGETS := $(OBJFILES) $(LIB)
DEPFILES := $(patsubst %.c,%.d,$(SOURCES))
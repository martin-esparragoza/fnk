LIB := common/libcommon.o
SOURCES := $(wildcard common/lib/*.c)
OBJFILES := $(patsubst %.c,%.o,$(SOURCES))
TARGETS := $(OBJFILES) $(LIB)
DEPFILES := $(patsubst %.c,%.d,$(SOURCES))
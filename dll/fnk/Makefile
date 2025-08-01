SOURCES := $(wildcard dll/fnk/lib/*.c) $(wildcard dll/fnk/src/*.c)
OBJFILES := $(patsubst %.c,%.o,$(SOURCES))
UPPEROBJS := arch/$(ARCH).o common/common.o comp/$(CC).o
TARGETS := $(OBJFILES) dll/fnk.fnk
DEPFILES := $(patsubst %.c,%.d,$(SOURCES))
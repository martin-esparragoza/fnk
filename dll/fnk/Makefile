SOURCES := $(wildcard dll/fnk/lib/*.c)
OBJFILES := $(patsubst %.c,%.o,$(SOURCES))
SPECIAL_FLAGS = -fno-pic -fno-pie -fno-asynchronous-unwind-tables
CFLAGS += $(SPECIAL_FLAGS)
LDFLAGS += $(SPECIAL_FLAGS)
UPPEROBJS := arch/$(ARCH).o common/common.o comp/$(CC).o
TARGETS := $(OBJFILES) dll/fnk.fnk
DEPFILES := $(patsubst %.c,%.d,$(SOURCES))
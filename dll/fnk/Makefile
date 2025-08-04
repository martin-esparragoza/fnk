SOURCES := $(wildcard dll/fnk/lib/*.c)
OBJFILES := $(patsubst %.c,%.o,$(SOURCES))
CFLAGS += -fno-pic -fno-pie
LDFLAGS += -no-pie
LIBFILES := arch/lib$(ARCH).o common/libcommon.o comp/lib$(CC).o
TARGETS := $(OBJFILES) dll/fnk/fnk-intermediate.o dll/fnk.fnk
DEPFILES := $(patsubst %.c,%.d,$(SOURCES))

$(LIBFILES):
	@
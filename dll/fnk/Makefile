SOURCES := $(wildcard dll/fnk/lib/*.c)
OBJFILES := $(patsubst %.c,%.o,$(SOURCES))
CFLAGS += \
	-fno-pic \
	-fno-pie \
	-fno-asynchronous-unwind-tables
LDFLAGS += # I don't think this needs no-pie
#-no-pie
LIBFILES := common/libcommon.o
TARGETS := $(OBJFILES) dll/fnk/fnk-intermediate.o dll/fnk.fnk
DEPFILES := $(patsubst %.c,%.d,$(SOURCES))

$(LIBFILES):
	@
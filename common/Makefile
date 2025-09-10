LIB := common/libcommon.o
SOURCES := $(wildcard common/lib/*.c)
OBJFILES := $(patsubst %.c,%.o,$(SOURCES))
TARGETS := $(OBJFILES) $(LIB)
DEPFILES := $(patsubst %.c,%.d,$(SOURCES))

# TODO: maybe make common have a native compilation? and then you can link it and everything will be fine. This also allows you to create a generic errcstr function
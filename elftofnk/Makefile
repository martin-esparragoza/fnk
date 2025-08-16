LIBSOURCES := $(wildcard elftofnk/lib/*.c)
# TODO: Under construction
SOURCES := $(wildcard elftofnk/*.c)
LIBFILES := log.o
OBJFILES := $(patsubst %.c,%.o,$(SOURCES))
TARGETS := $(OBJFILES)
DEPFILES := $(patsubst %.c,%.d,$(SOURCES))
CNATIVELINK += -lbfd
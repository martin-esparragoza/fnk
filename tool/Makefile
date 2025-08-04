SOURCES := $(wildcard tool/*.c)
OBJFILES := $(patsubst %.c,%.o,$(SOURCES))
TARGETS := $(OBJFILES)
DEPFILES := $(patsubst %.c,%.d,$(SOURCES))
CNATIVELINK += -lelf
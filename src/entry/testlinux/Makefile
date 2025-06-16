# This file must produce entry.o

SOURCES = $(wildcard *.c)
DEPFILES = $(patsubst %.c,%.d,$(SOURCES))
OBJFILES = $(patsubst %.c,%.o,$(SOURCES))
# Not allowed to access libs
INCFLAGS = -I../../../include/arch/$(ARCH) -I../../../include/comp/$(CC)

.PHONY: all build clean

all: build

clean:
	rm -rf *.o
	rm -rf *.d
	
build: $(OBJFILES)
	
%.o: %.c
	$(CC) $(CFLAGS) -MMD -MP $(INCFLAGS) -c $< -o $@ $(CLINK)
	
ifneq ($(MAKECMDGOALS),clean)
-include $(DEPFILES)
endif
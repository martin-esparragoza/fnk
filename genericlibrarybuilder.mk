# Inputs:
#	LIB = libname
#	SOURCES = Sources to compile
#	INCFLAGS = Include flags for the sources compilation

DEPFILES := $(patsubst %.c,%.d,$(SOURCES))
OBJFILES := $(patsubst %.c,%.o,$(SOURCES))

.PHONY: clean

clean:
	rm -rf $(LIB)
	rm -rf $(DEPFILES)
	rm -rf $(OBJFILES)
	
$(LIB): $(OBJFILES)
	$(LD) $(LDFLAGS) -r -o $@ $^

include ../rules.mk

include ../depsgrab.mk
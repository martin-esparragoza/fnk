## 3 step build process
# 1. Generate the starting build dependencies
# 2. Lookup to generate the list of objects
# 3. Imported makefile does the final binary assembly if needed

# Set this yourself
ARCH := testlinux

LD := gcc
LDFLAGS :=

CC := gcc
CFLAGS := -Wall -ffreestanding -std=c99 -fno-stack-protector -flto
CLINK :=

INCFLAGS := -I ./ -I arch/$(ARCH)/include/ -I comp/$(CC)/include/


MAKEDIRS := arch/ \
			comp/ \
			common/ \
			boot/src/entry/$(ARCH)/ \
			boot/src/ \
			boot/
#comp/ common/ boot/ dll/ kernel/
.PHONY: all clean $(MAKEDIRS)
all: $(MAKEDIRS)

ifeq ($(BUILDTARGET),)
# Enumerate
$(MAKEDIRS):
	$(MAKE) BUILDTARGET=$@
clean:
	$(foreach d,$(MAKEDIRS),$(MAKE) BUILDTARGET=$d clean;)
else
# Defines all of our variables like TARGETS, DEPFILES, and OBJFILES
include $(BUILDTARGET)/Makefile

# Now we are in the process of building. Lets turn this build target into its requirements
include rules.mk
.PHONY: all inc-depfiles clean
all: inc-depfiles $(TARGETS) # Attempt to make them
inc-depfiles:
-include $(DEPFILES)
clean:
	rm -rf $(TARGETS)
	rm -rf $(OBJFILES)
	rm -rf $(DEPFILES)
endif
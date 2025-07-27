## 3 step build process
# 1. Generate the starting build dependencies
# 2. Lookup to generate the list of objects
# 3. Imported makefile does the final binary assembly if needed

# Set this yourself
ARCH := testlinux

LD := ld
LDFLAGS :=

CC := gcc
CFLAGS := -Wall -ffreestanding -std=c99 -fno-stack-protector -flto
CLINK :=

INCFLAGS := -I ./ -I arch/$(ARCH)/include/ -I comp/$(CC)/include/


MAKEDIRS := arch/
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


#ARCH_O := arch/$(ARCH)/$(ARCH).o
#COMP_O := comp/$(CC)/$(CC).o
#COMMON_O := common/common.o
#BOOT := boot_$(ARCH)
#MAKEDIRS := arch/ comp/ common/ boot/

#.PHONY: all build clean $(ARCH_O) $(COMP_O) $(COMMON_O) $(BOOT) $(MAKEDIRS)
	
# TODO: All assemble
#all: build

# TODO: add dll/ and kernel/
#build: $(ARCH_A) $(COMP_A) $(COMMON_A) $(BOOT)

#clean: $(MAKEDIRS) 
	
#$(ARCH_A):
#	$(MAKE) -C arch $(notdir $@)

#$(COMP_A):
#	$(MAKE) -C comp $(notdir $@)

#$(COMMON_A):
#	$(MAKE) -C common $(notdir $@)

#$(BOOT):
#	$(MAKE) -C boot $@

# This is for make clean so it passes through
#include makedirs.mk
## 3 step build process
# 1. Generate the starting build dependencies
# 2. Lookup to generate the list of objects
# 3. Imported makefile does the final binary assembly if needed

# Set this yourself
ARCH := testlinux

LD := ld
LDFLAGS :=
LDLINK :=

CCNATIVE := gcc
CNATIVEFLAGS := -O3 -Wall -std=c99
CNATIVELINK :=

CC := gcc
CFLAGS := \
	-Wall \
	-ffreestanding \
	-std=c99 \
	-fno-stack-protector \
	-fno-asynchronous-unwind-tables \
	-fno-unwind-tables
CLINK :=

OBJCOPY := objcopy

INCFLAGS := -I ./ -I arch/$(ARCH)/include/ -I comp/$(CC)/include/


MAKEDIRS := arch/ \
			comp/ \
			elftofnk/ \
			common/ \
			boot/src/entry/$(ARCH)/ \
			boot/src/ \
			boot/ \
			dll/fnk
.PHONY: all clean $(MAKEDIRS)
all: $(MAKEDIRS)

ifeq ($(BUILDTARGET),)
# Enumerate
$(MAKEDIRS):
	$(MAKE) BUILDTARGET=$@
clean:
	$(foreach d,$(MAKEDIRS),$(MAKE) BUILDTARGET=$d clean;)
else
# Defines all of our variables like TARGETS and DEPFILES
include $(BUILDTARGET)/Makefile

# Now we are in the process of building. Lets turn this build target into its requirements
include rules.mk
-include $(BUILDTARGET)/ruleoverride.mk # This is specifically so they can override stuff defined in rules.mk like %.o
.PHONY: all inc-depfiles clean # inc-depfiles because we need the depfiles to be included before we build anything
all: inc-depfiles $(TARGETS) # Attempt to make them
inc-depfiles:
-include $(DEPFILES)
clean:
	rm -rf $(TARGETS)
	rm -rf $(DEPFILES)
endif
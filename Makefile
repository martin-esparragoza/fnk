## 3 step build process
# 1. Generate the starting build dependencies
# 2. Lookup to generate the list of objects
# 3. Imported makefile does the final binary assembly if needed

# Set this variable yourself (this is the TARGET compilation not the native one)
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

INCFLAGS := -I ./ -I arch/$(ARCH)/include/ -I comp/$(CC)/include/

MAKEDIRS := arch \
			comp \
			elftofnk \
			common \
			boot/src/entry/$(ARCH) \
			boot/src \
			boot #\
			#dll/fnk
.PHONY: all clean $(MAKEDIRS)

ifeq ($(BUILDTARGET),)
# Enumerate
all:
	$(MAKE) $(MAKEDIRS)
clean:
	$(MAKE) $(MAKEDIRS) MAKECMDARGS=$@
$(MAKEDIRS):
	$(MAKE) BUILDTARGET=$@ $(MAKECMDARGS)
else
all: $(MAKEDIRS) # Ok. Genuinely I have no clue why this works. It makes the ENTIRE thing work, I added it a while ago, and now I don't know what the hell it does
# Defines all of our variables like TARGETS and DEPFILES
include $(BUILDTARGET)/Makefile

# Now we are in the process of building. Lets turn this build target into its requirements
include rules.mk
-include $(BUILDTARGET)/ruleoverride.mk # This is specifically so they can override stuff defined in rules.mk like %.o
.PHONY += all buildprereq clean # buildprereq because we need the depfiles to be included before we build anything + for the target dir to be made
all: buildprereq $(TARGETS) # Attempt to make them
buildprereq:
-include $(DEPFILES)
clean:
	@echo removing $(TARGETS) $(DEPFILES)
	@rm -rf $(TARGETS)
	@rm -rf $(DEPFILES)
endif
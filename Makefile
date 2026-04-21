#
# Makefile for FNaF Advance
#

all : release



#ifeq ($(MAKECMDGOALS),)
#	MAKECMDGOALS := release
#	$(info "Target not set, built release by default.")
#	$(info "If you don't want to build release, please call `make debug` or another target." )
#endif

ifndef DEVKITPRO
	$(error DEVKITPRO is undefined (if using an IDE, check the environment variables the IDE can see))
endif

ifndef DEVKITARM
	$(error DEVKITARM is undefined (if using an IDE, check the environment variables the IDE can see))
endif

PATH := $(DEVKITARM)/bin:$(PATH)
PATH := $(DEVKITPRO)/tools/bin:$(PATH)
LIBTONC_PATH := $(DEVKITPRO)/libtonc
LIBTONC_INCLUDE := $(LIBTONC_PATH)/include
LIBTONC_A := $(LIBTONC_PATH)/lib/libtonc.a

# --- Project details -------------------------------------------------

PROJ    := FNaF_Advance
TITLE   := $(PROJ)

# https://stackoverflow.com/a/18258352
rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

# .h file for debug functions
DEBUG_H := include/debug.h

# get .c files
SRC_FILES := $(call rwildcard,source,*.c)
ASSET_FILES := $(call rwildcard,assets,*.c)
C_FILES := $(SRC_FILES) $(ASSET_FILES)

# .o files to compile
COBJS := $(patsubst %.c,%.o,$(C_FILES))

ifeq ($(MAKECMDGOALS),debug)
	FLAGS := -DDEBUG
else
	#ifeq ($(MAKECMDGOALS),release)
	FLAGS := -DRELEASE
endif

#DEPS := $(patsubst %.o,%.d,$(COBJS))
#-include $(DEPS)

# targets for .elf (all .o, plus libtonc.a)
OBJS	:= $(COBJS) $(SOBJS) $(DEBUG_H) $(LIBTONC_A)

# --- boot type (MB=0 : normal. MB=1 : multiboot) ---

MB = 0

ifeq ($(MB),1)
	TARGET	:= out/$(PROJ).mb
	SPECS	:= -specs=gba_mb.specs
else
	TARGET	:= out/$(PROJ)
	SPECS	:= -specs=gba.specs
endif

# --- Compiling -------------------------------------------------------

CROSS	?= arm-none-eabi-
AS		:= $(CROSS)as
CC		:= $(CROSS)gcc
LD		:= $(CROSS)gcc
OBJCOPY	:= $(CROSS)objcopy


ARCH	:= -mthumb-interwork -mthumb

ASFLAGS	:= -mthumb-interwork
CFLAGS	:= $(ARCH) -O2 -Wall -fno-strict-aliasing -I$(LIBTONC_INCLUDE) -Isource -Iassets -Iinclude $(FLAGS)
LDFLAGS	:= $(ARCH) $(SPECS)


# --- Targets -----------------------------------------------------------

debug: clean-deps clean-code rom

rebuild-assets: clean-assets rom

release: clean rom clean-assets clean-code clean-deps

rom : $(TARGET).gba

$(TARGET).gba : $(TARGET).elf
	$(OBJCOPY) -v -O binary $< $@
	-@gbafix $@ -t$(TITLE)

$(TARGET).elf : $(OBJS)
	$(LD) $^ $(LDFLAGS) -o $@

$(COBJS) : %.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

# $(CC) $(CFLAGS) -c -MM -MF $(patsubst %.o,%.d,$@) $< -o $@

# Rule for assembling .s -> .o files
$(SOBJS) : %.o : %.s
	$(AS) $(ASFLAGS) -c $< -o $@

# --- Clean -----------------------------------------------------------

clean-assets:
	@rm -fv $(patsubst %.c,%.o,$(ASSET_FILES))

clean-code:
	@rm -fv $(patsubst %.c,%.o,$(SRC_FILES))

clean-deps:
	@rm -fv $(DEBUG_OBJ)

clean-build:
	@rm -fv $(TARGET).gba
	@rm -fv $(TARGET).elf

clean : clean-assets clean-code clean-deps clean-build
#@rm -fv $(DEPS)

#EOF

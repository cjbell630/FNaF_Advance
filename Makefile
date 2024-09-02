#
# Makefile for FNaF Advance
#

PATH := $(DEVKITARM)/bin:$(PATH)
LIBTONC_PATH := $(DEVKITARM)/lib/tonclib
LIBTONC_INCLUDE := $(LIBTONC_PATH)/include
LIBTONC_A := $(LIBTONC_PATH)/lib/libtonc.a

# --- Project details -------------------------------------------------

PROJ    := FNaF_Advance
TITLE   := $(PROJ)

# https://stackoverflow.com/a/18258352
rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

# get .c files
SRC_FILES := $(call rwildcard,source,*.c)
ASSET_FILES := $(call rwildcard,assets,*.c)
C_FILES := $(SRC_FILES) $(ASSET_FILES)

# .o files to compile
COBJS := $(patsubst %.c,%.o,$(C_FILES))

SOBJS   := include/DWedit/debug.o

# targets for .elf (all .o, plus libtonc.a)
OBJS	:= $(COBJS) $(SOBJS) $(LIBTONC_A)

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
CFLAGS	:= $(ARCH) -O2 -Wall -fno-strict-aliasing -I$(LIBTONC_INCLUDE)
LDFLAGS	:= $(ARCH) $(SPECS)

.PHONY : build clean

# --- Build -----------------------------------------------------------

build : $(TARGET).gba


$(TARGET).gba : $(TARGET).elf
	$(OBJCOPY) -v -O binary $< $@
	-@gbafix $@ -t$(TITLE)

$(TARGET).elf : $(OBJS)
	$(LD) $^ $(LDFLAGS) -o $@

$(COBJS) : %.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule for assembling .s -> .o files
$(SOBJ) : %.o : %.s
	$(AS) $(ASFLAGS) -c $< -o $@
# --- Clean -----------------------------------------------------------

clean : 
	@rm -fv *.gba
	@rm -fv *.elf
	@rm -fv *.o

#EOF

#
# key_demo.mak
#
# Makefile for key demonstration
#
# NOTE: for educational purposes only. For real work, use 
# devkitPro's templates ( $(DEVKITPRO)/examples/gba/template )
# or tonclib's templates ( $(TONCCODE)/lab/template )

PATH := $(DEVKITARM)/bin:$(PATH)

# --- Project details -------------------------------------------------

PROJ    := FNaF_Advance
TITLE   := $(PROJ)

COBJS   := source/main.o include/tonc/toolbox.o assets/images/backgrounds/office/office.o \
			assets/images/sprites/buttons/buttons.o assets/images/sprites/buttons/buttons_apower.o \
			source/init.o source/menu.o assets/images/backgrounds/menu/menu.o source/game.o \
			assets/images/backgrounds/newspaper/newspaper.o

SOBJS   := include/DWedit/debug.o

OBJS	:= $(COBJS) $(SOBJS)

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
CFLAGS	:= $(ARCH) -O2 -Wall -fno-strict-aliasing
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

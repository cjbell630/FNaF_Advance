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

###CFILES := source/*.c source/**/*.c source/**/**/*.c assets/images/backgrounds/**/*.c assets/images/cams/*.c assets/images/sprites/**/*.c \
          			include/tonc/*.c

###COBJS  :=  $(CFILES:.c=.o)

###COBJS := source/*.c source/**/*.c source/**/**/*.c assets/images/backgrounds/**/*.c assets/images/cams/*.c assets/images/sprites/**/*.c \
          			include/tonc/*.c


### this is so fucking stupid
COBJS := \
			source/main.o source/init.o \
			source/game/menu.o source/game/game.o \
			source/game/control/camera.o source/game/control/game_clock.o \
			source/game/graphics/bg_pal_handler.o source/game/graphics/static_handler.o \
			source/util/random.o \
			\
			assets/images/backgrounds/office/office.o assets/images/backgrounds/error/error.o \
			assets/images/backgrounds/menu/menu.o assets/images/backgrounds/newspaper/newspaper.o \
			assets/images/backgrounds/loading/loading.o assets/images/backgrounds/static/static.o \
			assets/images/cams/stage_empty.o assets/images/cams/stage_bcf_s.o \
			assets/images/sprites/buttons/buttons.o assets/images/sprites/buttons/buttons_apower.o \
			assets/images/sprites/cam_map/cam_map.o

SOBJS   := include/DWedit/debug.o

OBJS	:= $(COBJS) $(SOBJS) include/tonclib/libtonc.a

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

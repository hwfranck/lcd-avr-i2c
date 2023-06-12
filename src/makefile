# Based on the WinAVR Makefile Template written by Eric B. Weddington, Jörg Wunsch, et al.
# https://github.com/embecosm/winavr/blob/master/Mfile/data/makefile_template.winavr
MCU = atmega2560
F_CPU = 16000000
TARGET = lcd_avr_i2c

# Optimize for size
OPT = s

# Debugging format.
DEBUG = dwarf-2

# Place -D or -U options here for C sources
CDEFS = -DF_CPU=$(F_CPU)UL

#---------------- Compiler Options C ----------------
#	-g*:		generate debugging information
#	-O*:		optimization level
#	-f...:		tuning, see GCC manual and avr-libc documentation
#	-Wall...:	warning level
#	gnu99:		c99 plus GCC extensions
CFLAGS = -g$(DEBUG)
CFLAGS += $(CDEFS)
CFLAGS += -O$(OPT)
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += -fpack-struct
CFLAGS += -fshort-enums
CFLAGS += -funsigned-bitfields
CFLAGS += -funsigned-char
CFLAGS += -Wall
CFLAGS += -Wstrict-prototypes
CFLAGS += -std=gnu99

#---------------- Linker Options ----------------
LDFLAGS = -Wl,--gc-sections
LDFLAGS += -Wl,--relax

#---------------- Programming Options (avrdude) ----------------
AVRDUDE_BAUD = 115200
# On Windows AVRDUDE_PORT = COM3
# On Ubuntu  AVRDUDE_PORT = /dev/ttyXXXn
AVRDUDE_PORT = /dev/ttyACM0
AVRDUDE_PROGRAMMER = wiring
# AVRDUDE_VERBOSE = -v -v
AVRDUDE_WRITE_FLASH = -U flash:w:$(TARGET).hex

AVRDUDE_FLAGS = -p $(MCU) -P $(AVRDUDE_PORT) -c $(AVRDUDE_PROGRAMMER) -b $(AVRDUDE_BAUD) -D
AVRDUDE_FLAGS += $(AVRDUDE_VERBOSE)

#============================================================================
CC = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

# Define all source and object files.
SRC = i2c.c lcd.c main.c
OBJ = $(SRC:%.c=%.o)

# Combine all necessary flags and optional flags.
ALL_CFLAGS = -mmcu=$(MCU) -I. $(CFLAGS)

# Default target.
all: $(TARGET).hex

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex -j .text -j .data $< $@

$(TARGET).elf: $(OBJ)
	$(CC) $(ALL_CFLAGS) $^ --output $@ $(LDFLAGS)

%.o : %.c
	$(CC) -c $(ALL_CFLAGS) $< -o $@

# cleaning targets for windows and linux
clean_linux:
	rm -f *.elf *.hex *.o

clean_win:
	del *.elf *.hex *.o

# flash
flash: $(TARGET).hex
	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_WRITE_FLASH)

#
.PHONY : all clean_linux clean_win flash
.PRECIOUS : $(OBJ)
.SECONDARY : $(TARGET).elf

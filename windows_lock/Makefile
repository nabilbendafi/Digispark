MCU = attiny85
F_CPU = 16500000

TARGET = windows_lock
SIZE = avr-size
CC = avr-gcc
OBJCOPY = avr-objcopy
OPTIMISE = -ffunction-sections -fdata-sections -ffreestanding
CFLAGS = -std=gnu99 -Wall -Os -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Iusbdrv -I.
LDFLAGS = -mmcu=$(MCU) -Wl,--gc-sections -Wl,--relax

SOURCES = usbdrv/usbdrv.c usbdrv/oddebug.c usbdrv/usbdrvasm.c main.c

OBJECTS = $(filter-out $(SOURCES), $(patsubst %.c,%.o,$(SOURCES)) $(patsubst %.S,%.o,$(SOURCES)))

all: $(TARGET).hex

clean:
	rm -f $(OBJECTS) $(TARGET).hex $(TARGET).elf

$(TARGET).elf: $(OBJECTS)
	@echo Linking $<
	@$(CC) $(LDFLAGS) -o $@ $(OBJECTS)
	@$(SIZE) --mcu=$(MCU) --format=avr $@

$(TARGET).hex: $(TARGET).elf
	@echo Creating hex File
	@$(OBJCOPY) -j .text -j .data -O ihex $< $@
 
%.o: %.c
	@echo Compiling $<
	$(CC) $(CFLAGS) $(OPTIMISE) -c $< -o $@
 
%.o: %.S
	@echo Assembling $<
	@$(CC) $(CFLAGS) $(OPTIMISE) -c $< -o $@

MCU = attiny85
F_CPU = 12000000

TARGET = blink
SIZE = avr-size
CC = avr-gcc
OBJCOPY = avr-objcopy
CFLAGS = -std=gnu99 -Wall -Os -mmcu=$(MCU) -DF_CPU=$(F_CPU)
LDFLAGS = -mmcu=$(MCU) -Wl,--gc-sections -Wl,--relax

SOURCES = main.c

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
	@echo Assembling $&lt;
	@$(CXX) $(CFLAGS) $(OPTIMISE) -c $&lt; -o $@

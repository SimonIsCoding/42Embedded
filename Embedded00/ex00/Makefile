#Variables:
MCU			= atmega328p
F_CPU		= 16000000UL
BAUD		= 115200
PORT		= /dev/ttyUSB0
PROGRAMMER	= arduino

CC			= avr-gcc
OBJCOPY		= avr-objcopy
AVRDUDE		= avrdude

all: 	hex flash

hex:	main.c
		$(CC) -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os main.c -o main.bin
		$(OBJCOPY) -O ihex main.bin main.hex

flash:	hex
		$(AVRDUDE) -c $(PROGRAMMER) -p $(MCU) -P $(PORT) -b $(BAUD) -U flash:w:main.hex:i

clean:
	rm -rf main.hex main.bin

.PHONY: all clean hex flash

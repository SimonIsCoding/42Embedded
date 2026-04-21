#Variables:
MCU			= atmega328p
F_CPU		= 16000000UL
BAUD		= 115200
PORT		= /dev/ttyUSB1
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

asm:
		$(CC) -mmcu=$(MCU) -DF_CPU=$(F_CPU) -S -fverbose-asm -Os main.c -o main.s

disasm:
	$(CC) -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os main.c -o main.bin
	# -S : mélange le code source C et l'assembleur
	# -d : désassemble les sections d'instructions
	# -C : "demangle" les noms (utile pour le C++)
	# -j .text : ne montre que la section de code (évite les données inutiles)
	avr-objdump -S -d -C -j .text main.bin > main.lst

clean:
	rm -rf main.hex main.bin main.s main.lst

.PHONY: all clean hex flash

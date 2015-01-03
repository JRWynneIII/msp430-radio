SRC=morse.c
all:
	msp430-elf-gcc -mmcu=msp430g2553 $(SRC) -O1

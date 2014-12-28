SRC=morse.c
all:
	msp430-elf-gcc -mmcu=msp430g2231 $(SRC) -O1

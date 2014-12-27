SRC=morse.c
all:
	msp430-elf-g++ -mmcu=msp430g2231 $(SRC)

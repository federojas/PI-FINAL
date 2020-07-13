COMPILER=gcc
FLAGS=-pedantic -std=c99 -Wall -fsanitize=address
all: VAN BUE     

VAN: OUTPUT_FILE=finalVAN
VAN: mainVAN.c
	$(COMPILER) -o $(OUTPUT_FILE) mainVAN.c treesADT.c hoodADT.c $(FLAGS)

BUE: OUTPUT_FILE=finalBUE
BUE: mainBUE.c
	$(COMPILER) -o $(OUTPUT_FILE) mainBUE.c treesADT.c hoodADT.c $(FLAGS)


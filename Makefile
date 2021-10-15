compiler = gcc
flags = -Wall -Og
dependecies = bsp.c
files = *.c

main:
	$(compiler) $(flags) $(files) -o bsp 

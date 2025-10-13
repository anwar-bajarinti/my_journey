cc=arm-none-eabi-gcc
mach=cortex-m4
cflags=-c -mcpu=$(mach) -mthumb -std=gnu11 -O0
main.o:main.c
	$(cc) $(cflags) $^ -o $@
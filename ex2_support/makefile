# Exercise 2, TDT4258
# Authors: Bao, Gøran, Håvard.

CC=arm-none-eabi-gcc
LD=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy

WARNING_FLAGS=-Wall -Wextra -Werror -pedantic
OPTIMIZATION_FLAGS=-O3
LIBRARY_FLAGS=-lm -lgcc -lc -lcs3 -lcs3unhosted -lefm32gg

CFLAGS=-mcpu=cortex-m3 -mthumb -g -std=c99 $(OPTIMIZATION_FLAGS) $(WARNING_FLAGS)
LDFLAGS=-mcpu=cortex-m3 -mthumb -g $(OPTIMIZATION_FLAGS) $(LIBRARY_FLAGS) -Llib 
ASFLAGS=-mcpu=cortex-m3 -mthumb -g $(OPTIMIZATION_FLAGS)
LINKERSCRIPT=lib/efm32gg.ld

.PHONY: clean upload

all: upload

upload: ex2.bin
	-eACommander.sh -r --address 0x00000000 -f "ex2.bin" -r

ex2.bin: ex2.elf
	${OBJCOPY} -O binary $< $@

ex2.elf: ex2.c timer1.o dac.o gpio.o nvic.o prs.o led.o interrupt_handlers.o
	${LD} -T ${LINKERSCRIPT} $^ -o $@ ${LDFLAGS} 

timer1.o: timer1.c timer1.h
	${CC} ${CFLAGS} -c $< -o $@

dac.o: dac.c dac.h
	${CC} ${CFLAGS} -c $< -o $@

gpio.o: gpio.c gpio.h
	${CC} ${CFLAGS} -c $< -o $@

nvic.o: nvic.c nvic.h
	${CC} ${CFLAGS} -c $< -o $@

prs.o: prs.c prs.h
	${CC} ${CFLAGS} -c $< -o $@

led.o: led.c led.h
	${CC} ${CFLAGS} -c $< -o $@

interrupt_handlers.o: interrupt_handlers.c interrupt_handlers.h
	${CC} ${CFLAGS} -c $< -o $@

clean:
	-rm -rf *.o *.elf *.bin *.hex 

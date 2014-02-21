# Example Makefile
#
# Exercise 2, TDT4258

CC=arm-none-eabi-gcc
LD=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy

WARNING_FLAGS=-Wall -Wextra -Werror -pedantic
OPTIMIZATION_FLAGS=-O3
CFLAGS=-mcpu=cortex-m3 -mthumb -g -std=c99 $(OPTIMIZATION_FLAGS)  $(WARNING_FLAGS)
LDFLAGS=-mcpu=cortex-m3 -mthumb -g $(OPTIMIZATION_FLAGS) -lgcc -lc -lcs3 -lcs3unhosted -lefm32gg -Llib 
ASFLAGS=-mcpu=cortex-m3 -mthumb -g $(OPTIMIZATION_FLAGS)
LINKERSCRIPT=lib/efm32gg.ld

ex2.bin: ex2.elf
	${OBJCOPY} -O binary $< $@

ex2.elf: ex2.o
	${LD} -T ${LINKERSCRIPT} $^ -o $@ ${LDFLAGS} 

ex2.c: timer.c dac.c gpio.c interrupt_handlers.c nvic.c
	${CC} ${CFLAGS} -c $< -o $@

.PHONY: clean upload
upload: ex2.bin
	-eACommander.sh -r --address 0x00000000 -f "ex2.bin" -r

clean:
	-rm -rf *.o *.elf *.bin *.hex 

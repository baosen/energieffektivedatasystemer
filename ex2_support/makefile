# Example Makefile
#
# Exercise 2, TDT4258

CC=arm-none-eabi-gcc
LD=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy

CFLAGS=-mcpu=cortex-m3 -mthumb -g -std=c99 -Wall -O3 -Wextra -Werror -pedantic
LDFLAGS=-mcpu=cortex-m3 -mthumb -g -lgcc -lc -lcs3 -O3 -lcs3unhosted -lefm32gg -Llib 
ASFLAGS=-mcpu=cortex-m3 -mthumb -g -O3
LINKERSCRIPT=lib/efm32gg.ld

ex2.bin : ex2.elf
	${OBJCOPY} -O binary $< $@


ex2.elf: ex2.o
	${LD} -T ${LINKERSCRIPT} $^ -o $@ ${LDFLAGS} 

ex2.c: timer.c dac.c gpio.c interrupt_handlers.c nvic.c
	${CC} ${CFLAGS} -c $< -o $@

#%.o : %.c %.h
	#${CC} ${CFLAGS} -c $< -o $@

#ex2.elf : ex2.o timer.o dac.o gpio.o interrupt_handlers.o nvic.o
	#${LD} -T ${LINKERSCRIPT} $^ -o $@ ${LDFLAGS} 

.PHONY : clean upload
clean :
	-rm -rf *.o *.elf *.bin *.hex 

upload :
	-eACommander.sh -r --address 0x00000000 -f "ex2.bin" -r

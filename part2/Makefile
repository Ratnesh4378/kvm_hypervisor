all: matrix matrix-a matrix-b guest1.bin guest2.bin

matrix:
	gcc matrix.c -o matrix -lpthread

matrix-a:
	gcc matrix-a.c -o matrix-a

matrix-b:
	gcc matrix-b.c -o matrix-b

guest1.bin: guest1.o
	ld -m elf_i386 --oformat binary -N -e _start -Ttext 0x10000 -o guest1.bin guest1.o

guest2.bin: guest2.o
	ld -m elf_i386 --oformat binary -N -e _start -Ttext 0x10000 -o guest2.bin guest2.o

guest1.o: guest1.s
	as -32 guest1.s -o guest1.o

guest2.o: guest2.s
	as -32 guest2.s -o guest2.o

.PHONY: clean
clean:
	$(RM) matrix guest1.bin guest1.o \
		guest2.bin guest2.o matrix-a matrix-b
	

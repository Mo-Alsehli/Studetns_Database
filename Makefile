all exe: main.c studentsFifo.c studentsFifo.h fifo.c fifo.h
	gcc -c main.c -I . -o main.o
	gcc -c studentsFifo.c -I . -o studentsFifo.o
	gcc -c fifo.c -I . -o fifo.o
	gcc main.o fifo.o studentsFifo.o -o exe
	./exe
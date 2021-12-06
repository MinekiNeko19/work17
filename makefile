all: write.o control.o
	gcc -o write write.o
	gcc -o control control.o

control.o: control.h control.c
	gcc -c control.c

write.o: write.h write.c
	gcc -c write.c
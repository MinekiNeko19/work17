all: control.o write.o
	gcc -o semaphone control.o write.o

control.o: control.h control.c
	gcc -c control.c

write.o: write.h write.c
	gcc -c write.c

run:
	./semaphone
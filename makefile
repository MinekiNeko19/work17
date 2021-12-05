all: write.o control.o
	gcc -o semaphone write.o control.o

control.o: control.h control.c
	gcc -c control.c

write.o: write.h write.c
	gcc -c write.c

run:
	./semaphone
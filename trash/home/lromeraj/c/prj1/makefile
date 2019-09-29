main: main.o diary.o
	gcc main.o diary.o -o main
main.o: main.c
	gcc -c main.c
diary.o: diary.h diary.c
	gcc -c diary.c

clean:
	rm -rf *.o main

run:
	./main

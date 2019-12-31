all: fileinfo.o execute.o fileops.o main.o
	gcc -o fileexp fileinfo.o execute.o fileops.o main.o

fileinfo.o: fileinfo.c fileinfo.h structs.c
	gcc -c fileinfo.c

execute.o: execute.c execute.h fileinfo.h
	gcc -c execute.c

fileops.o: fileops.c fileops.h
	gcc -c fileops.c

main.o: main.c fileinfo.h execute.h
	gcc -c main.c

run:
	./fileexp

clean:
	rm *.o
	rm fileexp
	rm *.gch

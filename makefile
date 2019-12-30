all: fileinfo.o execute.o main.o
	gcc -o fileexp fileinfo.o execute.o main.o

fileinfo.o: fileinfo.c fileinfo.h
	gcc -c fileinfo.c

execute.o: execute.c execute.h fileinfo.h
	gcc -c execute.c

main.o: main.c fileinfo.h execute.h
	gcc -c main.c

run:
	./fileexp

clean:
	rm *.o
	rm fileexp
	rm *.gch

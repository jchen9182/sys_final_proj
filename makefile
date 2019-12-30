all: fileinfo.o main.o
	gcc -o fileexp fileinfo.o main.o

fileinfo.o: fileinfo.c fileinfo.h
	gcc -c fileinfo.c

main.o: main.c fileinfo.h
	gcc -c main.c

run:
	./fileexp

clean:
	rm *.o
	rm fileexp
	rm *.gch

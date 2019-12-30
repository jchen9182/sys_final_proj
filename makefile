all: getfiles.o main.o
	gcc -o fileexp getfiles.o main.o

getfiles.o: getfiles.c getfiles.h
	gcc -c getfiles.c

main.o: main.c getfiles.h
	gcc -c main.c

run:
	./fileexp

clean:
	rm *.o
	rm fileexp
	rm *.gch

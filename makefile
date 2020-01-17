all: main

main: main.c fileinfo.h execute.h fileops.h structs.c
	gcc `pkg-config --cflags gtk+-3.0` -o fileexp main.c structs.c fileinfo.c execute.c fileops.c `pkg-config --libs gtk+-3.0`

run:
	./fileexp

clean:
	#rm *.o
	rm fileexp
	rm *.gch

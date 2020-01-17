all: main

main: main.c fileinfo.h execute.h fileops.h
	gcc `pkg-config --cflags gtk+-3.0` -o fileexp main.c fileinfo.c execute.c fileops.c `pkg-config --libs gtk+-3.0`

run:
	./fileexp

clean:
	#rm *.o
	rm fileexp
	rm *.gch

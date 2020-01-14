all: main

main: main.c fileinfo.h execute.h
	gcc `pkg-config --cflags gtk+-3.0` -o fileexp main.c fileinfo.c `pkg-config --libs gtk+-3.0`

run:
	./fileexp

clean:
	#rm *.o
	rm fileexp
	rm *.gch

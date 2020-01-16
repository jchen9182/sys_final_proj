command = -o fileexp main.c fileinfo.c execute.c fileops.c

all: main

main: main.c fileinfo.h execute.h fileops.h
	cc `pkg-config --cflags gtk+-3.0` -DGDK_VERSION_MIN_REQIRED=GDK_VERSION_3_3 $(command) `pkg-config --libs gtk+-3.0`

run:
	./fileexp

clean:
	#rm *.o
	rm fileexp
	rm *.gch

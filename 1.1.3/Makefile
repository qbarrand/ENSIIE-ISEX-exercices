all: fileutils.o myread.o pg4.c
	gcc fileutils.o myread.o pg4.c -o pg4

fileutils.o: fileutils.c
	gcc -o $@ -c fileutils.c

myread.o: myread.c
	gcc -o $@ -c myread.c

clean:
	rm *.o
	rm pg4
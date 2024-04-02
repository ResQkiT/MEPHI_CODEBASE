matrix.o: matrix.c
	gcc -g -c matrix.c

integer.o: integer.c
	gcc -g -c integer.c

complex.o: complex.c
	gcc -g -c complex.c

double.o: double.c
	gcc -g -c double.c
	

main.o: main.c
	gcc -g -c main.c

testmain.o: testmain.c
	gcc -g -c testmain.c


testmain: testmain.o matrix.o integer.o complex.o double.o
	gcc testmain.o matrix.o  integer.o complex.o double.o -o testmain

main: main.o matrix.o  integer.o complex.o double.o
	gcc main.o matrix.o  integer.o complex.o double.o -o main


matrix.o: matrix.c
	gcc -g -c matrix.c

integer.o: integer.c
	gcc -g -c integer.c

complex.o: complex.c
	gcc -g -c complex.c

testmain.o: testmain.c
	gcc -g -c testmain.c

double.o: double.c
	gcc -g -c double.c

app: matrix.o testmain.o integer.o complex.o double.o
	gcc matrix.o testmain.o integer.o complex.o double.o -o app
main.o: main.cpp
	g++ -g -c main.cpp

Sequence.o: Sequence.cpp
	g++ -g -c Sequence.cpp

ArraySequence.o: ArraySequence.cpp
	g++ -g -c ArraySequence.cpp

DynamicArray.o: DynamicArray.cpp
	g++ -g -c DynamicArray.cpp


main: main.o DynamicArray.o Sequence.o ArraySequence.o 
	g++ main.o Sequence.o Sequence.o ArraySequence.o -o main
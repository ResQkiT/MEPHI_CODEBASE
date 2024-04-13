
Sequence.o: Sequence.cpp
	g++ -g -c Sequence.cpp

ArraySequence.o: ArraySequence.cpp
	g++ -g -c ArraySequence.cpp

DynamicArray.o: DynamicArray.cpp
	g++ -g -c DynamicArray.cpp

main.o: main.cpp
	g++ -g -c main.cpp

main.app: main.o DynamicArray.o Sequence.o ArraySequence.o 
	g++  Sequence.o  ArraySequence.o DynamicArray.o main.o -o main.app


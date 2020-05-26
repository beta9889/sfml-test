.PHONY: all

all : exe

main.o: test.cpp
	g++ -c test.cpp -o main.o
exe: main.o
	g++ main.o -lsfml-window -lsfml-graphics -lsfml-system -lsfml-network -o exe

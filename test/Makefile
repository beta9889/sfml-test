.PHONY: all

all : exe

main.o: main.cpp
	g++ -c main.cpp -o main.o
exe: main.o
	g++ main.o -lsfml-window -lsfml-graphics -lsfml-system -lsfml-network -o exe

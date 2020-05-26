.PHONY: all

all : exe

main.o: main.cpp
	g++ -c main.cpp -ISFML/include -o main.o
exe: main.o
	g++ main.o -LSFML/lib -lsfml-window -lsfml-graphics -lsfml-system -lsfml-network -o exe

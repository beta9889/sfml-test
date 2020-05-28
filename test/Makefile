.PHONY: all

all : exe

server.o: server.cpp
	g++ -c server.cpp -ISFML/include -o server.o
exe: server.o
	g++ server.o -LSFML/lib -lsfml-window -lsfml-graphics -lsfml-system -lsfml-network -o exe

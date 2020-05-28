.PHONY: all
.PHONY: client
.PHONY: exe

all : exe client

main.o: main.cpp
	g++ -c main.cpp -ISFML/include -o main.o
exe: main.o
	g++ main.o -LSFML/lib -lsfml-window -lsfml-graphics -lsfml-system -lsfml-network -o exe


client : Client.o
	g++ Client.o -LSFML/LIB -lsfml-window -lsfml-graphics -lsfml-system -lsfml-network -o client

Client.o : Client.cpp
	g++ -c Client.cpp -ISFML/include -o Client.o

cli : client


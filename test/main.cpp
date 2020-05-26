#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <thread>
using namespace std;
void server (int port){
	
	sf::TcpListener lyssnar;

	
	if (lyssnar.listen(port) != sf::Socket::Done){
		cout << "error listening\n";
    	}
	
	sf::TcpSocket Koppling;
	if (lyssnar.accept(Koppling) != sf::Socket::Done){
		cout << "error connection\n";
	}

	cout << "function finished, connected?\n";

	char message[255];
	cout << "what message do you want to send?\n";
	cin >> message;

	if(Koppling.send(message,255) != sf::Socket::Done){

		cout << "doesn't work\n";
	}
	else {
		cout << "it worked";

	}
	cin >> port;
}
//-------------------------------------------------------------------
void client (int port){
	cout << "vilken ip?\n";
	sf::IpAddress ip;
	cin >> ip;

	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect(ip,port);
	if (status != sf::Socket::Done){
		cout << "error \n";
	}
	else{
		cout << "connected\n";
	}	
	char message[255];
	size_t TaEmot;
	if(socket.receive(message, 255, TaEmot) != sf::Socket::Done){
		cout << "connected but no message recieved\n";
	}
	else{
		cout << message;

	}
}
//---------------------------------------------------------------------

int main()
{ 
    
    int port;
    port = 53000;

    cout << "server (s)  eller klient (k)? \n";
    char resultat;
    char null; 
    cin >> resultat;

    if (resultat == 's'){
	 server(port);
	 resultat == null;
    }
    else if (resultat = 'k'){
	client(port);		
    	resultat = null;
    }

/*
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
*/
    return 0;
}

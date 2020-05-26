#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <thread>
using namespace std;
void server (int port){
	
    sf::TcpListener lyssnar;
    	if (lyssnar.listen(port) != sf::Socket::Done){
		    cout << "error \n";
    	}
    	else {
		    cout << "connected\n";
    	}
}
void client (int port){
	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect(ip,port);
	if (status != sf::Socket::Done){
		cout << "error \n";
	}
	else{
		cout << "connected\n";
	}	
}
int main()
{ 
    
    cout << "vilken port ? \n";
    int port;
    cin >> port;

    cout << "server (s)  eller klient (k)? \n";
    char resultat;
    char null; 
    cin >> resultat;
    resultat = null;

    if (resultat = 's'){
	    std::thread connection (server,port);
	   connection.join();
    }
    else if (resultat = 'k'){
	client(port);	

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

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
using namespace std;

int main()
{ 

    cout << "server (s)  eller klient (k)? \n";
    char resultat;
    char null; 
    cin >> resultat;
    resultat = null;
    if (resultat = 's'){
    	sf::TcpListener lyssnar;
    	cout << "vilken port ? \n";
    	int port;
    	cin >> port;
    	if (lyssnar.listen(port) != sf::Socket::Done){
		    cout << "error \n";
    	}
    	else {
		    cout << "connected";
    	}
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

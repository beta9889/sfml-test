#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

void Choose(int Port);
void ClientTCP(int Port);
void ServerTCP(int Port);

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works... ONLINE?!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    int Port = 1234;
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            Choose(Port);
            
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}

void Choose(int Port){
  char vem; 
  std::cout << "Skriv porten på servern du vill ansluta till:";
  std::cin >> Port; 
  std::cout << "Vill du vara server: 's' \nEller vill du vara en klient: 'k'"; 
  std::cin >> vem;
 
  if (vem == 's'){ 
    ServerTCP(Port); 
  } 
  else{
    ClientTCP(Port); 
  } 
}
//___________________________________________________________________
void ClientTCP(int Port){
  sf::IpAddress ServerAddress;
  char Send[50] = "Hejs svejs i cyberspace!";

  std::cout << "Skriv addressen på servern du vill ansluta till:";
  std::cin >> ServerAddress;
  sf::TcpSocket socket;
  sf::Socket::Status status = socket.connect(ServerAddress, Port);
  if(status != sf::Socket::Done){
    std::cout << "failed to connect the server" << std::endl;
  }
  status;
  if(socket.send(Send, 50) != sf::Socket::Done){
    std::cout << "failed to send message" << std::endl;
  }
}
//___________________________________________________________________
void ServerTCP(int Port){
  sf::TcpListener listener;

  if(listener.listen(Port) != sf::Socket::Done){
    std::cout << "error" << std::endl;
  }
  sf::TcpSocket Client;
  if(listener.accept(Client) != sf::Socket::Done){
    std::cout << "errbor" << std::endl;
  }

}

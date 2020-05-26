#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>

void Choose(int Port);
void ClientTCP(int Port);
void ServerTCP(int Port);
void receivemess();
std::size_t received;
char storage[2000];
sf::TcpSocket socket;
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
            receivemess();
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
  std::string SendC = "Hejs svejs i cyberspace!";

  std::cout << "Skriv addressen på servern du vill ansluta till:";
  std::cin >> ServerAddress;

  socket.connect(ServerAddress, Port);

  socket.send(SendC.c_str(), SendC.length() + 1);
}
//___________________________________________________________________
void ServerTCP(int Port){
  sf::IpAddress IP = sf::IpAddress::getLocalAddress();
  std::cout << "Address: " << IP << std::endl;
  std::string SendS = "You hacked it to the server!";
  sf::TcpListener listener;

  listener.listen(Port);
  listener.accept(socket);
  socket.send(SendS.c_str(), SendS.length() + 1);
}
//______________________________________________________________________-
void receivemess(){

  socket.receive(storage, sizeof(storage), received);
  std::cout << storage << std::endl;
}

#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

void Choose();
void ClientTCP(unsigned short Port);
void ServerTCP(unsigned short Port);
std::size_t received;
char storage[2000];

//__________________________________________________________________
int main()
{
  Choose();
  std::cout << storage << std::endl;

  system("pause");

  return 0;
   
}
//__________________________________________________________________
void Choose(){
  unsigned short Port = 53000;
  char vem; 
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
void ClientTCP(unsigned short Port){
  sf::IpAddress ServerAddress;
  sf::TcpSocket socket;
  std::string SendK = "Hejs svejs i cyberspace!";

  std::cout << "Skriv addressen på servern du vill ansluta till:" << std::endl;
  std::cin >> ServerAddress;

  sf::Socket::Status status = socket.connect(ServerAddress, Port);
  if (status != sf::Socket::Done){
    std::cout << "error \n";
  }
  else{
    std::cout << "connected\n";
    socket.send(SendK.c_str(), SendK.length() + 1);
    socket.receive(storage, sizeof(storage), received);
  }
}
//___________________________________________________________________
void ServerTCP(unsigned short Port){

  std::string SendS = "You hacked it to the server!";
  sf::TcpListener listener;

  if (listener.listen(Port) != sf::Socket::Done){
    std::cout << "error listening\n";
  }
  sf::TcpSocket Koppling;
  if (listener.accept(Koppling) != sf::Socket::Done){
    std::cout << "error connection\n";
  }
  Koppling.send(SendS.c_str(), SendS.length() + 1);
  Koppling.receive(storage, sizeof(storage), received);
}


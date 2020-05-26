#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

void Choose(unsigned short Port);
void ClientTCP(unsigned short Port);
void ServerTCP(unsigned short Port);
void receivemess();
std::size_t received;
char storage[2000];
sf::TcpSocket socket;
//__________________________________________________________________
int main()
{
  unsigned short Port = 1234;
  Choose(Port);
  receivemess();

  return 0;
   
}
//__________________________________________________________________
void Choose(unsigned short Port){
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
void ClientTCP(unsigned short Port){
  sf::IpAddress ServerAddress;
  std::string SendC = "Hejs svejs i cyberspace!";

  std::cout << "Skriv addressen på servern du vill ansluta till:";
  std::cin >> ServerAddress;

  socket.connect(ServerAddress, Port);

  socket.send(SendC.c_str(), SendC.length() + 1);
}
//___________________________________________________________________
void ServerTCP(unsigned short Port){
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

  system("pause")
}

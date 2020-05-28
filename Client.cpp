#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <thread>

using namespace std;

class Myclass{
  public: 
    int HP;
    int Mana;
    string name;
    int val;
    int sendturn;	
  private:
}Spelare[2];

sf::Packet packet;
sf::Packet packet2;
sf::Packet& operator <<(sf::Packet& packet, const Myclass& myclass){
  return packet << myclass.HP << myclass.Mana << myclass.name << myclass.val;
}
sf::Packet& operator >>(sf::Packet& packet, Myclass& myclass){
  return packet >> myclass.HP >> myclass.Mana >> myclass.name >> myclass.val >> myclass.sendturn;
}

sf::TcpSocket socket;
int port = 50000;
//----------------------------------------------------------
void client (){
  cout << "vilken ip?\n";
  sf::IpAddress ip;
  cin >> ip;

  sf::Socket::Status status = socket.connect(ip,port);
  if (status != sf::Socket::Done){
    cout << "error connecting";
  }
  else{
    cout << "connected\n";
  }
}
//----------------------------------------------------------
void round(){				
  packet >> Spelare[0];
  packet2 >> Spelare[1];
  packet.clear();
  packet2.clear();

  if(Spelare[0].HP <= 0){
    cout << "clienten vann\n";
    return ;
  }
  if(Spelare[1].HP <= 0){
    cout << "Servern vann\n";
    return ;
  }

  cout << Spelare[0].name << "'s HP: " << Spelare[0].HP << " Mana: " << Spelare[0].Mana << endl; 
  cout << Spelare[1].name << "'s HP: " << Spelare[1].HP << " Mana: " << Spelare[1].Mana << endl; 
 

  if(Spelare[0].sendturn == 1){
    int x;
    cout << "Vill Klienten casta spell: \n1:Curse of Madness\n2:Breath of Frost\n";
    cin >> x;
    Spelare[1].val = x;
    packet << Spelare[0];
    packet2 << Spelare[1];

    if(socket.send(packet) != sf::Socket::Done){
      cout << "error sending message";
    }
    if(socket.send(packet2) != sf::Socket::Done){
      cout << "error sending message2";
    }
  } 
  else {
    cout << "det är " << Spelare[0].name << "'s tur\n";
  }
}
//---------------------------------------------------
int main(){     
  int loop = 0;
  client();
  while(loop == 0){ 
    if(socket.receive(packet) != sf::Socket::Done){
      socket.disconnect();
    }
    else{
      if(socket.receive(packet2) != sf::Socket::Done){
        socket.disconnect();
      }
      else{
        round();
        packet.clear();
        packet2.clear();
      }
    }
  }
}

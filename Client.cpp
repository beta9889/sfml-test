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
  private:
}Spelare[2];

sf::Packet packet;
sf::Packet& operator <<(sf::Packet& packet, const Myclass& myclass){
  return packet << myclass.HP << myclass.Mana << myclass.name << myclass.val;
}
sf::Packet& operator >>(sf::Packet& packet, Myclass& myclass){
  return packet >> myclass.HP >> myclass.Mana >> myclass.name << myclass.val;
}

sf::TcpSocket socket;
int port = 53000;
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
  int turn;				
  packet >> Spelare[0] >> turn;
  cout << Spelare[0].name << "'s HP: " << Spelare[0].HP << "Mana: " << Spelare[0].Mana << endl; 
//  cout << Spelare[1].name << "'s HP: " << Spelare[1].HP << "Mana: " << Spelare[1].Mana << endl; 
  

  if(turn == 1){
    int x;
    cout << "Vill Klienten använda spell \n1:Curse of Madness\n2:Breath of Löfven\n";
    cin >> x;
    Spelare[0].val = x;//ska vara 1 sen
    packet << Spelare[0];//ska vara 1 sen

    if(socket.send(packet) != sf::Socket::Done){
      cout << "error sending message";
    }
    else {
      cout << "it worked\n";
    }
  } 
  else {
    cout << "det är " << Spelare[0].name << "'s tur\n";
  }
}
//---------------------------------------------------
int main(){     

  client();
  sf::TcpSocket socket;

  if(socket.receive(packet) != sf::Socket::Done){
    cout << "error recieving packet\n";
  }
  else{
    round();
    packet.clear();
  }
}

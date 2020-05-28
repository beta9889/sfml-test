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
  return packet << myclass.HP << myclass.Mana << myclass.name << myclass.val << myclass.sendturn;
}
sf::Packet& operator >>(sf::Packet& packet, Myclass& myclass){
  return packet >> myclass.HP >> myclass.Mana >> myclass.name >> myclass.val >> myclass.sendturn;
}
sf::TcpListener lyssnar;
sf::TcpSocket Koppling;
int port = 50000;

//--------------------------------------------------------
void castspell(int x, int turn){
  int motstandare;
  motstandare = turn + 1;
  if(motstandare == 2){
    motstandare = 0;
  }
  if(x == 1){
    cout << Spelare[turn].name << " is Casting Curse of Madness\n";
    Spelare[turn].Mana = Spelare[turn].Mana - 10;
    Spelare[motstandare].HP = Spelare[motstandare].HP - 10;
  }
  if(x == 2){
    cout << Spelare[turn].name << " is Casting Breath of Löfven\n";
    Spelare[turn].Mana = Spelare[turn].Mana - 20; 
    Spelare[motstandare].HP = Spelare[motstandare].HP - 20;   
  }
}
//-------------------------------------------------------
void sendclient(int turn){
  
  if(Koppling.receive(packet) != sf::Socket::Done){
    cout << "connected but no message recieved\n";
  }
  else{
    cout << "Jag fick tillbaka packet1\n";
    packet >> Spelare[0];
  }
  if(Koppling.receive(packet2) != sf::Socket::Done){
    cout << "connected but no message recieved\n";
  }
  else{  
    cout << "Jag fick tillbaka packet2\n";
    packet2 >> Spelare[1];
    cout << Spelare[1].val << endl;
    castspell(Spelare[1].val, turn);
  }
  packet2.clear();
  packet.clear();
}
//-------------------------------------------------------
void sendroundinfo(int turn){
  Spelare[0].sendturn = turn;
  packet << Spelare[0];
  packet2 << Spelare[1];

  if(Koppling.send(packet) != sf::Socket::Done){
    cout << "doesn't work\n";
  }
  else {
    cout << "it worked\n";
  }
  if(Koppling.send(packet2) != sf::Socket::Done){
    cout << "doesn't work2\n";
  }
  else {
    cout << "it worked2\n";
  }
  packet.clear();
  packet2.clear();

//-------------------------------------------------------
  cout << Spelare[0].name << "'s HP: " << Spelare[0].HP << "Mana: " << Spelare[0].Mana << endl; 
  cout << Spelare[1].name << "'s HP: " << Spelare[1].HP << "Mana: " << Spelare[1].Mana << endl; 
}
//-------------------------------------------------------
void serverturn(int turn){
  int x;
  cout << "Vill Servern casta spell: \n1:Curse of Madness\n2:Breath of Frost\n";
  cin >> x;
  castspell(x, turn);
}
//--------------------------------------------------------
int main(){
  Spelare[0].HP = 100;
  Spelare[0].Mana = 100;
  Spelare[1].HP = 100;
  Spelare[1].Mana = 100;
  Spelare[0].name = "Servern";
  Spelare[1].name = "Klienten";
  cout << "Welcome we are waiting for a connection\n";
  if (lyssnar.listen(port) != sf::Socket::Done){
    cout << "error listening\n";
  }
 	
  if (lyssnar.accept(Koppling) != sf::Socket::Done){
    cout << "error connection\n";
  }
  else{
    cout << "connected\n";
  }
  int turn = 0;
  while (Spelare[0].HP > 0 && Spelare[1].HP > 0){
    if(turn == 2){
      turn = 0;
    }
    sendroundinfo(turn);
    if (turn == 1){
      cout << "De är " << Spelare[turn].name << "'s tur\n";
      sendclient(turn);
    }
    else{
      cout << "De är " << Spelare[turn].name << "'s tur\n";
      serverturn(turn);
    }
    turn = turn + 1;
  }
  if(Spelare[0].HP <= 0){
    cout << "clienten vann\n";
  }
  if(Spelare[1].HP <= 0){
    cout << "Servern vann\n";
  }
}

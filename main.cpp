#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

using namespace std;

class Myclass{
  public: 
    int HP;
    int Mana;
    string name;
    int val;	
  private:
}Spelare[2];

//sf::Packet packet;
//sf::Packet& operator <<(sf::Packet& packet, const MyClass& myclass){
//  return packet << myclass.HP << myclass.Mana << myclass.name << myclass.val;
//}
//sf::Packet& operator >>(sf::Packet& packet, MyClass& myclass){
//  return packet >> myclass.HP >> myclass.Mana >> myclass.name << myclass.val;
//}


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
//skicka till client 
  cout << "låt client sköta runda härifrån\n"; 
//  Spelare[turn].castspell(x, turn);
}
//-------------------------------------------------------
void sendendroundinfo(){
//skicka statsen efter rundan till clienten
  cout << "SKicka härifrån stats and shit\n";

}
//-------------------------------------------------------
void serverturn(int turn){
  int x;
  cout << "Vill du använda spell \n1:Curse of Madness\n2:Breath of Löfven\n";
  cin >> x;
  castspell(x, turn);
  x = 0;
  turn = turn + 1;
}
//--------------------------------------------------------
int main(){
  Spelare[0].HP = 100;
  Spelare[0].Mana = 100;
  Spelare[1].HP = 100;
  Spelare[1].Mana = 100;
  Spelare[0].name = "Server";
  Spelare[1].name = "Klient";
  int turn = 0;
  while (Spelare[0].HP > 0 && Spelare[1].HP > 0){
    if(turn == 2){
      turn = 0;
    }
    cout << "De är " << Spelare[turn].name << "'s tur\n";
    if (turn == 1){
      sendclient(turn);
    }
    else{
      serverturn(turn);
    }
    sendendroundinfo();
  }
  if(Spelare[0].HP <= 0){
    cout << "clienten vann\n";
  }
  if(Spelare[1].HP <= 0){
    cout << "Servern vann\n";
  }
}

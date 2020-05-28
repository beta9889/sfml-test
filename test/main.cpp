#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

//---------------------------------------------------------------------------
/*
sf::Packet& intopacket(sf::Packet& packet, const battle& battle){

	return packet << battle.playerHP << battle.opponentHP;
}
sf::Packet& outpacket(sf::Packet& packet, cont battle& battle){
	return packet >> battle.playerHP >> battle.opponentHP;
}
*/
struct battle{
	public:
	int opponentHP = 10;
	int playerHP = 10;
	void printshit(sf::Uint8 playerHP, sf::Uint8 opponentHP){
		
		cout <<"Player Hp = "<< playerHP << endl;
		cout <<"Opponent HP = "<< opponentHP << endl;
	}
};

void server (int port){
	
	sf::TcpListener lyssnar;

	
	if (lyssnar.listen(port) != sf::Socket::Done){
		cout << "error listening "<< endl;
    	}
	
	sf::TcpSocket Koppling;
	if (lyssnar.accept(Koppling) != sf::Socket::Done){
		cout << "error connecting "<< endl;
	}

	cout << "function finished, connected\n";


	string input;
	sf::Packet message;
	sf::Packet PHP;
	sf::Packet OHP;

	battle battle;	
	battle.playerHP=10;
	battle.opponentHP=10;	
	for (int i=0; i<10;i++){
		cout << "what message do you want to send?\n";

		getline(cin >> ws ,input);
		battle.printshit(battle.playerHP,battle.opponentHP);	

		if(message << input){
			if(PHP << battle.playerHP){
				if(OHP<<battle.opponentHP) {
					cout << "message in packet\n";
				}
			}
		}
		else{
			cout << "package could not recieve info \n";
		}


		if(Koppling.send(message) != sf::Socket::Done){
			if(Koppling.send(PHP) != sf::Socket::Done){
				if(Koppling.send(OHP) != sf::Socket::Done){
					cout << "error sending message\n";
				}
			}
		}
		else {
			cout << "message sent\n";
		
		}
	
		cout << "Waiting for a responce\n";
		message.clear();

		if(Koppling.receive(message) != sf::Socket::Done){

			cout << "there was a issue\n";
		}
		else{
			if(message >> input){ 
				message.clear();	
	
				cout <<"you got a responce\n"<< input<<endl;
			}
		}
			
		battle.playerHP =battle.playerHP - 2;
		battle.opponentHP = battle.opponentHP - 5;
		if (battle.playerHP <= 0) break;
		else if (battle.opponentHP <= 0) break;
	}

	cout << "enter e to exit the program\n";
	cin.ignore(1000,'e');
	Koppling.disconnect();
}

//-------------------------------------------------------------------

void client (int port){
	cout << "What ip adress?\n";
	sf::IpAddress ip;
	cin >> ip;

	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect(ip,port);
	if (status != sf::Socket::Done){
		cout << "error connecting";
	}
	else{
		cout << "connected\n";
	}
	
	sf::Packet message;
	string output;
	battle Cbattle;
	sf::Packet PHP;
	sf::Packet OHP;

	Cbattle.playerHP=10;
	Cbattle.opponentHP=10;	

	for (int i=0;i<10;i++){
		if(socket.receive(message) != sf::Socket::Done){
			
			if(socket.receive(PHP) != sf::Socket::Done){
				if(socket.receive(OHP) != sf::Socket::Done){
					cout << "error recieving message\n";
				}
			}
		}
		else{
			if(message >> output){
				cout<<" här är medelandet  \"" << output <<"\" "<<endl;
				if(PHP >> Cbattle.opponentHP){
					if(OHP >> Cbattle.playerHP){
						cout << Cbattle.opponentHP << endl << Cbattle.playerHP << endl;
					}
				}
			}

		}
	
		message.clear();

		cout << "what do you want to respond with?\n";
		string input;
		getline(cin >>ws, input);

		if(message << input){
			socket.send(message);
			cout << "message sent\n";
		}
		else{
			cout << "there was a error\n";
		}
	
		if (Cbattle.playerHP <= 0) break;
		else if (Cbattle.opponentHP <= 0) break;
		else {Cbattle.playerHP = 0; Cbattle.opponentHP=0;}
	}
	cout <<"enter e to exit the program" <<endl;
	cin.ignore(1000,'e');
	socket.disconnect();
}

//---------------------------------------------------------------------

int main()
{ 
    
	int port;
	port = 52000;

	cout << "server (s)  eller klient (k)? \n";
	char resultat;
	char null; 
	cin >> resultat;

	if (resultat == 's'){
		resultat == null;
		server(port);
    }

	else if (resultat = 'k'){
		resultat = null;
		client(port);		
    }

    return 0;
}

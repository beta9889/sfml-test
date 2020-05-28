#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <cstring>
using namespace std;


class character
{
	public:
	int hp = 100;
	void kick(character &server1);
	void punch(character &client1);
	void hello();

};

//---------------------------------------------------------------------------
/*void punch(character &client1)
{
	client1.hp = client1.hp - 50;
	cout << client1.hp << endl;
	

}*/
void character::kick(character &server1)
{
	server1.hp = server1.hp - 50;
	cout << server1.hp << endl;
	

}

void server (int port, character &server1){
character func_call;
	
	sf::TcpListener lyssnar;

	
	if (lyssnar.listen(port) != sf::Socket::Done){
		cout << "error listening "<< endl;
    	}
	
	sf::TcpSocket Koppling;
	if (lyssnar.accept(Koppling) != sf::Socket::Done){
		cout << "error connecting "<< endl;
	}

	cout << "function finished, connected?\n";

	cout << "what message do you want to send?\n";
	char message[10];
	for (int i; i<=10; i++){
		
		cin >> message[i];

	}
	//cin.getline(message,sizeof(message));

	if(Koppling.send(message,sizeof(message)) != sf::Socket::Done){

		cout << "error sending message";
	}
	else {
		cout << "it worked\n";

	}
	cout << "enter e to exit the program\n";
	cin.ignore(1000,'e');
	Koppling.disconnect();
}
//-------------------------------------------------------------------

void client (int port, character &server1){
character func_call;
	cout << "vilken ip?\n";
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
	
	char* message;
	size_t TaEmot;

	if(socket.receive(message, 1000, TaEmot) != sf::Socket::Done){
		cout << "error recieving message\n";
	}
	else{
		cout << message<<endl ;
		
	

	}
	cout <<"enter e to exit the program" <<endl;
	cin.ignore(256,'e');
	socket.disconnect();
}
//---------------------------------------------------------------------

int main()
{
character server1;
character client1;
character func_call;
    
	int port;
	port = 51000;

	cout << "server (s)  eller klient (k)? \n";
	char resultat;
	char null; 
	cin >> resultat;

	if (resultat == 's'){
		server(port, server1);
		resultat == null;
    }

	else if (resultat = 'k'){
		client(port, client1);		
		resultat = null;
    }
	/*do
	{
	func_call.kick(server1);
	cout << "ENEMY ATTACKING" << endl;
	func_call.punch(server1);
	}while(server1.hp >= 0 && client1.hp >= 0);
	return 0;

}*/

    return 0;
}

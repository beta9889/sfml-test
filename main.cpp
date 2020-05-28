#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

//---------------------------------------------------------------------------

void server (int port){
	
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
	sf::Packet message;
	string input;
	string output;
	for(int i; i<=10; i++){
		
		getline(cin >> ws, input);;

		if(Koppling.send(message) != sf::Socket::Done){

			cout << "error sending message";
		}
		else {
			cout << "it worked\n";

		}
	
		message.clear();
		if(Koppling.receive(message)){
			message >> output;
			cout << output << endl;
			
		}
		else{
			cout << "error try again \n";
		}

	}
	cout << "enter e to exit the program\n";
	cin.ignore(1000,'e');
	Koppling.disconnect();
}

//-------------------------------------------------------------------

void client (int port){
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
	
	sf::Packet message;
	string output;
	string input;
	for (int i; i<10;i++){
		if(socket.receive(message) != sf::Socket::Done){
			cout << "error recieving message\n";
		}
		else{
			message >> output;
			cout << "message is = "<< output <<endl;

		}
			
		
		getline(cin >> ws,input );;
		message.clear();
		if(socket.send(message) != sf::Socket::Done){

			cout << "error sending message";
		}
		else {
			cout << "it worked\n";

		}

	}
	cout <<"enter e to exit the program" <<endl;
	cin.ignore(256,'e');
	socket.disconnect();
}
//---------------------------------------------------------------------

int main()
{ 
    
	int port;
	port = 53000;

	cout << "server (s)  eller klient (k)? \n";
	char resultat;
	char null; 
	cin >> resultat;

	if (resultat == 's'){
		server(port);
		resultat == null;
    }

	else if (resultat = 'k'){
		client(port);		
		resultat = null;
    }

    return 0;
}

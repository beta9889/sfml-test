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
	char message[256];
	
	cin.getline(message,256);

	if(Koppling.send(message,256) != sf::Socket::Done){

		cout << "error sending message";
	}
	else {
		cout << "it worked\n";

	}
	cout << "enter e to exit the program\n";
	cin.ignore(1000,'e');
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
	
	char message[255];
	size_t TaEmot;

	if(socket.receive(message, 255, TaEmot) != sf::Socket::Done){
		cout << "error recieving message";
	}
	else{
		cout << message<<endl ;

	}
	cout <<"enter e to exit the program" <<endl;
	cin.ignore(256,'e');
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

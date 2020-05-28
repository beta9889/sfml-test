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

	string input;
	sf::Packet message;
	getline(cin >> ws ,input);
	
	//cout << input << endl;

	if(message << input){
		
		cout << "message in packet\n";
	}
	else{
		cout << "package could not recieve info \n";
	}

	
	//cin.getline(message,sizeof(message));

	if(Koppling.send(message) != sf::Socket::Done){

		cout << "error sending message\n";
	}
	else {
		cout << "it worked\n";
		
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

	if(socket.receive(message) != sf::Socket::Done){
		cout << "error recieving message\n";
	}
	else{
		if(message >> output){
			cout<<" här är medelandet: " << output <<endl;
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
	

	cout <<"enter e to exit the program" <<endl;
	cin.ignore(1000,'e');
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
		resultat == null;
		server(port);
    }

	else if (resultat = 'k'){
		resultat = null;
		client(port);		
    }

    return 0;
}

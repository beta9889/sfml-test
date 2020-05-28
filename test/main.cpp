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

	cout << "function finished, connected\n";


	string input;
	sf::Packet message;
	sf::Packet PHP;
	sf::Packet OHP;

		
	int playerHP=10;
	int opponentHP=15;	
	for (int i=0; i<10;i++){
		cout << "what message do you want to send?\n";

		getline(cin >> ws ,input);
		cout << playerHP << endl << opponentHP<<endl;	

		if(message << input){
		cout << "message packaged\n";
		}
		else{
			cout << "message could not recieve info \n";
		}
		if(Koppling.send(message) != sf::Socket::Done){
			cout << "error sending message";
		}
		else {
			cout << "message sent\n";
		}



		if(PHP << playerHP){
			cout << "Your HP packaged\n"; 

		}
		else{
			cout << "your HP could not be packaged\n";
		}


		if(Koppling.send(PHP) != sf::Socket::Done){
			cout << "error sending your HP"; 
		}
		else{
			cout << "Your HP was sent without problem";
		}



		if(OHP<<opponentHP) {
			cout << "Opponent HP packaged\n";
		}

		else{
			cout << "opponents HP could not be packaged\n";
		}

	
		if(Koppling.send(OHP) != sf::Socket::Done){
			cout << "error sending message\n";
		}
		else{
			cout << "Opponent HP sent successfully";
		}


		cout << "Waiting for a responce\n";
		message.clear();
		PHP.clear();
		OHP.clear();

		if(Koppling.receive(message) != sf::Socket::Done){

			cout << "there was a issue\n";
		}
		else{
			if(message >> input){ 
				message.clear();	
	
				cout <<"you got a responce\n"<< input<<endl;
			}
		}
			
		playerHP =playerHP - 2;
		opponentHP = opponentHP - 5;
		if (playerHP <= 0) break;
		else if (opponentHP <= 0) break;
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
	sf::Packet PHP;
	sf::Packet OHP;
	int playerHP=10;
	int opponentHP=10;	

	for (int i=0;i<10;i++){
		if(socket.receive(message) != sf::Socket::Done){
			cout << "error recieving message\n";
		}

		else{
			if(message >> output){
				cout<<" här är medelandet  \"" << output <<"\" "<<endl;
			}

		}


		if(socket.receive(PHP) != sf::Socket::Done){
			cout << "error recieving Player HP\n";
		}
		else{
			if(PHP >> opponentHP){
				cout << opponentHP << endl;
			}
			else{
				cout << "error reading Player health\n";
			}
		}

		if(socket.receive(OHP) != sf::Socket::Done){
			cout << "error recieving Opponent HP\n";	
		}
		else{
			if( OHP >> playerHP){
					cout << playerHP << endl;
			}
			else{
				cout << "could not read opponent HP\n"; 
			}

		}
	
		message.clear();
		PHP.clear();
		OHP.clear();

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
	
		if (playerHP <= 0) break;
		else if (opponentHP <= 0) break;
		else {playerHP = 0; opponentHP = 0;}
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

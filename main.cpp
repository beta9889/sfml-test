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
	string output = "Nothing! This is the first round :)";
		
	int playerHP=10;
	int opponentHP=10;	
	for (int i=0; i<10;i++){

		cout << "\n\nyour opponent Choose "<< output <<endl;
		cout << "Your HP = " << playerHP << endl;
		cout << "Your Opponents HP =" << opponentHP << endl;

		if(PHP << playerHP){
			//cout << "Your HP packaged\n"; 
			
		}
		else{
			cout << "your HP could not be packaged\n";
		}


		if(Koppling.send(PHP) != sf::Socket::Done){
			cout << "error sending your HP\n"; 
		}
		else{
			//cout << "Your HP was sent without problem\n";
		}


		if(OHP<<opponentHP) {
			//cout << "Opponent HP packaged\n";
		}

		else{
			cout << "opponents HP could not be packaged\n";
		}

	
		if(Koppling.send(OHP) != sf::Socket::Done){
			cout << "error sending message\n";
		}
		else{
			//cout << "Opponent HP sent successfully\n";
		}


		cout << "Do you want to attack(1) or block(2)?\n";

		getline(cin >> ws ,input);

		if(message << input){
			//cout << "message packaged\n";
		}
		else{
			cout << "message could not be packaged \n";
		}
		if(Koppling.send(message) != sf::Socket::Done){
			cout << "error sending message\n";
		}
		else {
			//cout << "message sent\n";
		}

		cout << "Waiting for a responce\n";
		message.clear();
		PHP.clear();
		OHP.clear();

		if(Koppling.receive(message) != sf::Socket::Done){

			cout << "there was a issue\n";
		}
		else{
			if(message >> output){ 
				message.clear();	
	
			//	cout <<"you got a responce\n"<< output<<endl;
			}
		}
		if (input == output) {
			message <<"Stalemate\n";
		       	playerHP-1; 
			opponentHP-1;
		}	
		
		else if( input == "1" && output == "2") {
			cout << "opponent blocked\n";
		       	message <<"you blocked\n"; 
			playerHP = playerHP - 2;
		}
		else if(input == "2" && output == "1"){ 
			cout << "you blocked\n";
			message << "opponent blocked\n";
			opponentHP = opponentHP - 2;
		
		}
		else {
			message << "both need a proper attack";
			cout << message << endl;
		}

		if (playerHP <= 0){ cout << "you have lost\n"; break;}
		else if (opponentHP <= 0) {cout <<"you have won\n";break;}
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
		cout << "error connecting\n";
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
	bool loop = true;	
	while (loop){
		if(socket.receive(PHP) != sf::Socket::Done){
			cout << "error recieving Player HP\n";
		}
		else{
			if(PHP >> opponentHP);
			else{
				cout << "error reading Player health\n";
			}
		}

		if(socket.receive(OHP) != sf::Socket::Done){
			cout << "error recieving Opponent HP\n";	
		}
		else{
			if( OHP >> playerHP);
			else{
				cout << "could not read opponent HP\n"; 
			}

		}
		
		cout << "your hp = " << playerHP << endl;
		cout << "your opponents hp = " << opponentHP << endl;
		
		message.clear();
		PHP.clear();
		OHP.clear();

		cout << "Do you want to attack(1) or block(2) \n";
		string input;
		getline(cin >>ws, input);

		if(message << input){
			socket.send(message);
			//cout << "message sent\n";
		}
		else{
			cout << "there was a error\n";
		}
	
		if(socket.receive(message) != sf::Socket::Done){
			cout << "error recieving message\n";
		}

		else{
			if(message >> output){
				if(output== input) cout << "\n\nyou picked the same option\n";
				else if(output == "1") cout << "\n\nYour Opponent attacked\n";
				else if(output == "2") cout << "\n\nYour Opponent blocked\n";
				else cout << "\n\nyour opponent picked a invalid option\n";
			}

		}


		if (playerHP <= 0){cout << "You lost\n"; break;}
		else if (opponentHP <= 0) {cout<<"You won\n"; break;}
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

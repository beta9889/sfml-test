#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

//Klasser
class connections
{
	public:
	void player(connections &port);
	void player2(connections &port);
	void server(connections &port);
	int current_port;
	int hp;
	sf::IpAddress ip;
};

//Funktionsdeklarationer

void connections::server(connections &port)
{
	sf::TcpListener listener;
	cout << "port: " << port.current_port << endl;
	if(listener.listen(port.current_port) != sf::Socket::Done)
	{
		cout << "Inga öppna anslutningar.." << endl;
		}
	sf::TcpSocket client;
	if (listener.accept(client) != sf::Socket::Done)
	{
		cout << "Aktiva anslutningar begärda(user1)" << endl;
	}
		
	sf::TcpSocket client2;
	if (listener.accept(client2) != sf::Socket::Done)
	{
		cout << "Aktiva anslutningar begärda(user2)" << endl;
	}
	cin.ignore(100, 'e');

}

void connections::player(connections &port)
{
	cout << "Skriv in IP-adressen till serverdatorn" << endl;
	cin >> port.ip;
	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect(port.ip, port.current_port);
	if(status != sf::Socket::Done)
	{
		cout << "Upptagen portanslutning eller felaktig IP-adress" << endl;
	}
	cin.ignore(100, 'e');

}
void connections::player2(connections &port)
{
	cout << "Skriv in IP-adressen till serverdatorn" << endl;
	cin >> port.ip;
	sf::TcpSocket socket2;
	sf::Socket::Status status = socket2.connect(port.ip, port.current_port);
	if(status != sf::Socket::Done)
	{
		cout << "Upptagen portanslutning eller felaktig IP-adress" << endl;
	}
	cin.ignore(100, 'e');

}


int main()
{
connections port;
connections protocol;
connections func_call;
int x = 0;
//--------------------
	cout << "Skriv in önskad port" << endl;
	cin >> port.current_port;
	cout << "Är du host(0), spelare(1) eller spelare(2)" << endl;
	cin >> x;
		if(x < 1){
		func_call.server(port);
		}else if(x > 0 && x < 2){
		func_call.player(port);
		}else if(x > 1){
		func_call.player2(port);
		}
	
}
	

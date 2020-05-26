#include <iostream>
//Enbart system- och nätverksmodulerna används
#include <SFML/System.hpp>
#include <SFML/Network.hpp> // MÅSTE finnas med för nätverksspel

#define SFML_STATIC //Se till så att det inte behövs extra DLL-filer

// using namespace std;    // utifall att konsollen behövs för felsöknning

// Funktionsdeklarationer

void DoClientTCP(unsigned short Port); 
void DoClientUDP(unsigned short Port); 
void DoServerTCP(unsigned short Port); 
void DoServerUDP(unsigned short Port); 

int main (int argc, char **argv)
{ // Välj valfritt nummer över 1024 för port, de < 1024 är reserverade
const unsigned short Port = 2435; 

// TCP eller UDP ? 
char Protocol; 
std::cout << "Vill du använda TCP ('t') eller UDP ('u') ? "; 
std::cin >> Protocol; 

// Klient eller server ? 
char Who; 
std::cout << "Vill du vara server ('s') eller en klient ('k') ? "; 
std::cin >> Who;
 
if (Who == 's') 
{ // Kör programmet som server 
if (Protocol == 't') 
DoServerTCP(Port); 
 else 
DoServerUDP(Port); 
} 
else 
{ // Kör programmet som klient 
if (Protocol == 't') 
DoClientTCP(Port); 
else DoClientUDP(Port); 
} 

// Vänta tills användaren trycker ner 'enter' tangenten
std::cout << "Tryck ner ENTER för att avsluta..." << std::endl; 
std::cin.ignore(10000, '\n'); 
std::cin.ignore(10000, '\n'); 

return 0; 
}

//FUNKTIONERNA

// ****************************************************** //
// Skapa en TCP klient och anslut till en startad server 
// ****************************************************** //
void DoClientTCP(unsigned short Port) 
{ // Fråga efter serverns adress
 sf::IPAddress ServerAddress; 
do { 
   std::cout << "Skriv adresss eller namn på servern du vill ansluta till : "; 
   std::cin >> ServerAddress; 
   } 
   while (!ServerAddress.IsValid());

   // Skapa en TCP socket för att kommunicera med servern
   sf::SocketTCP Client; 

   // Anslut till servern 
  if (Client.Connect(Port, ServerAddress) != sf::Socket::Done) 
  return; 
  std::cout << "Ansluten till server " << ServerAddress << std::endl; 

  // Få meddelande från en klient
  char Message[128]; 
  std::size_t Received; 
  if (Client.Receive(Message, sizeof(Message), Received) != sf::Socket::Done) 
  return; 
  // Visa upp meddelandet

  std::cout << "Meddelande mottaget från server : \"" << Message << "\"" << std::endl; 
  // Definiera ett meddelande att skicka tillbaka till servern
 char ToSend[] = "Hej, klient pratar !"; 

  // Skicka meddelandet
 if (Client.Send(ToSend, sizeof(ToSend)) != sf::Socket::Done) 
  return; 

  std::cout << "Meddelande skickat till server : \"" << ToSend << "\"" << std::endl; 
  // Stäng socketen när vi är klarar 
  Client.Close(); 
  } 
 
 // ****************************************************** //
 // Skapa en TCP server och vänta på inkommande meddelanden
// ****************************************************** //
 void DoServerTCP(unsigned short Port) 
 { // Skapa en TCP socket för att kommunicera med klienter
 sf::SocketTCP Server; 
 // Lyssna på en port för inkommande meddelanden
 if (!Server.Listen(Port)) 
 return; 

 std::cout << "Servern lyssnar på port " << Port << ", väntar på anslutning... " << std::endl; 

 // Vänta på kontakt 
 sf::IPAddress ClientAddress; 
 sf::SocketTCP Client; 
 Server.Accept(Client, &ClientAddress); 
 std::cout << "Klient ansluten : " << ClientAddress << std::endl; 

 // Skicka ett meddelande till klienten 
 char ToSend[] = "Hej, server meddelar"; 
 if (Client.Send(ToSend, sizeof(ToSend)) != sf::Socket::Done) 
 return; 

 std::cout << "Meddelande skickat till klient : \"" << ToSend << "\"" << std::endl; 
 // Motta meddelande från klienten
 char Message[128]; 
 std::size_t Received; 

if (Client.Receive(Message, sizeof(Message), Received) != sf::Socket::Done) 
return; 

// Visa meddelandet
 std::cout << "Meddelande mottaget från klient : \"" << Message << "\"" << std::endl; 
 // Stäng sockets när vi är klara
 Client.Close(); 
 Server.Close(); 
}


// ************************************************************** //
// Skapa en UDP klient och skicka meddelande med UDP till en server 
// ************************************************************** //
void DoClientUDP(unsigned short Port) 
{ // Fråga efter serverns IP-adress 
sf::IPAddress ServerAddress; 
do { 
   std::cout << "Skriv in IP-adressen eller namnet på servern du vill skicka ett meddelande till : ";
   std::cin >> ServerAddress; } 
while (!ServerAddress.IsValid()); 

// Skapa en UDP socket för att kunna kommunicera med servern
sf::SocketUDP Client; 
// Skicka ett meddelande till servern
char Message[] = "Hej, skickat av klient!"; 
if (Client.Send(Message, sizeof(Message), ServerAddress, Port) != sf::Socket::Done) 
   return; 
  
   std::cout << "Meddelande skickat till server : \"" << Message << "\"" << std::endl; 
   // Stäng ner socketen när det är klart
  Client.Close(); 
} 

// ****************************************************** //
// Starta en UDP server och vänta på inkommande meddelanden
// ****************************************************** //

void DoServerUDP(unsigned short Port) 
{ // Skapa en UDP socket för att kommunicera med klienten
sf::SocketUDP Server;

// Koppla den till en specifik port 
if (!Server.Bind(Port)) 
return; 

// Ta emot ett meddelande från vem som helst
sf::IPAddress ClientAddress; 
unsigned short ClientPort; 
char Message[128]; 
std::size_t Received; 

if (Server.Receive(Message, sizeof(Message), Received, ClientAddress, ClientPort) != sf::Socket::Done) 
return; 
// Visa upp det
std::cout << "Meddelande mottaget från " << ClientAddress << " från port " << ClientPort << " : \"" << Message << "\"" << std::endl; 
// Stäng socketen när vi är klara
Server.Close(); 
}

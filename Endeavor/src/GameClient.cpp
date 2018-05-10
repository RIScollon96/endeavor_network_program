#include "GameClient.h"
#include <iostream>

GameClient::GameClient(std::string ip_address, int port_num, EndeavorGame* endeavor_game)
{
	Poco::Net::initializeNetwork();
	Poco::Net::SocketAddress socket_addr(ip_address, port_num);
	connection = new Poco::Net::StreamSocket(socket_addr);
	
	endeavorGame = endeavor_game;
	
	client_thread = new Poco::Thread();
    client_thread->start(*this);
}

GameClient::~GameClient()
{
	std::cout << "destructor called" << std::endl;
	delete connection;
}

void GameClient::run()
{
	GameClient* game_client = this;
	
	//need to get message containing player number
	char* playerNumber = game_client->receive(connection);
	int numberPlayer = atoi(playerNumber);
	switch(numberPlayer)
	{
		case 1 : endeavorGame->setTitle("Red/Player1");
			break;
		case 2 : endeavorGame->setTitle("Purple/Player2");
			break;
		case 3 : endeavorGame->setTitle("Orange/Player3");
			break;
		case 4 : endeavorGame->setTitle("Blue/Player4");
			break;
		case 5 : endeavorGame->setTitle("Green/Player5");
			break;
	}
	
	while(!endeavorGame->isGameOver())
	{
		CSC2110::String xmlF = CSC2110::String(game_client->receive(connection));
		endeavorGame->setGameState(xmlF);
		if(numberPlayer == endeavorGame->getPlayerID())
		{
			endeavorGame->repaint();
			while(numberPlayer == endeavorGame->getPlayerID())
			{
				Sleep(500);
			}
			send(connection); 
		}
		else
		{
			endeavorGame->disableGame();
			endeavorGame->repaint();
		}
	}
	endeavorGame->disableGame();
	
}

char* GameClient::receive(Poco::Net::StreamSocket* connection)
{
	int buffer_size = 3000;
	char* buffer = new char[buffer_size];
	int num_bytes_received = 0;
	int buffer_index = 0;

	num_bytes_received += connection->receiveBytes(&buffer[buffer_index], 1);
	buffer_index = num_bytes_received - 1;
	
	while (buffer[buffer_index] != '\0')
	{  
		
		if (num_bytes_received == buffer_size)
		{
			char* tempBuffer = new char[buffer_size*2];
			for(int z=0; z<buffer_size;z++)
			{
				tempBuffer[z] = buffer[z];
			}
			buffer_size *= 2;
			buffer = tempBuffer;			
		}
		
		num_bytes_received += connection->receiveBytes(&buffer[buffer_index+1], buffer_size-buffer_index-1);
		std::cout << "num bytes received: " <<  num_bytes_received << std::endl;
		buffer_index = num_bytes_received - 1;
    }
	return buffer;
}

void GameClient::send(Poco::Net::StreamSocket* connection)
{
	std::cout << "sending bytes to client" << std::endl;
	
	CSC2110::String xmlFile = this->endeavorGame->getGameState();
	
	int xmlFileLength = xmlFile.length();
	
	int num_bytes_sent = connection->sendBytes(xmlFile.get_c_str(), xmlFileLength+1);
	std::cout << "num bytes sent: " <<  num_bytes_sent << std::endl;
	
}



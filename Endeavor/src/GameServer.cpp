#include "GameServer.h"

#include <iostream>
#include <string>

GameServer::GameServer(std::string ip_address, int port_num, int num_players, EndeavorGame* endeavor_game) 
{	
	Poco::Net::initializeNetwork();

	this->num_players = num_players;
	endeavorGame = endeavor_game;
	
	Poco::Net::SocketAddress socket_addr(ip_address, port_num);
	server_socket = new Poco::Net::ServerSocket(socket_addr);
	
	
	for(int i=0;i<num_players;i++)
	{
		client_connections[i] = server_socket->acceptConnection();
		int player_number = i + 1;
		std::string playerNumb = std::to_string(player_number);
		
		client_connections[i].sendBytes(playerNumb.c_str(), 2);
	}
	
	for(int i=0;i<num_players;i++)
	{
		send(&client_connections[i]);
	}

	server_thread = new Poco::Thread();
    server_thread->start(*this);
}

GameServer::~GameServer()
{
	std::cout << "destructor called" << std::endl;
	delete server_socket;
}

void GameServer::run()
{	
	GameServer* game_server = this;
	
	while(!endeavorGame->isGameOver())
	{
		int j=endeavorGame->getActivePlayer();
		
		endeavorGame->disableGame();
		CSC2110::String xml = CSC2110::String(game_server->receive(&client_connections[j-1]));
		endeavorGame->setGameState(xml);
		endeavorGame->repaint();
		
		for(int y=0;y<num_players;y++)
		{
			send(&client_connections[y]);
		}		
	}
	endeavorGame->disableGame();
}

char* GameServer::receive(Poco::Net::StreamSocket* connection)
{
	int buffer_size = 3000;  //what should this be set to?
	char* buffer = new char[buffer_size];
	int num_bytes_received = 0;
	int buffer_index = 0;
	
	//delete[] buffer;
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

void GameServer::send(Poco::Net::StreamSocket* connection)
{
	std::cout << "sending bytes to client" << std::endl;
	
	CSC2110::String xmlFile = this->endeavorGame->getGameState();
	int xmlFileLength = xmlFile.length();
	int num_bytes_sent = connection->sendBytes(xmlFile.get_c_str(), xmlFileLength+1);
	std::cout << "num bytes sent: " <<  num_bytes_sent << std::endl;
	
}



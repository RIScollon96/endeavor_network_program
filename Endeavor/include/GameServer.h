#if !defined GAME_SERVER
#define GAME_SERVER

//Poco includes must be first
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Runnable.h"
#include "Poco/Thread.h"
#include "EndeavorGame.h"

#include "String_.h"

class GameServer : public Poco::Runnable
{
   private:
		Poco::Net::StreamSocket client_connections[5];
		Poco::Net::ServerSocket* server_socket;
		Poco::Thread* server_thread;
		EndeavorGame* endeavorGame;
		int num_players;
		
   public:
		GameServer(std::string ip_address, int port_num, int num_players, EndeavorGame* endeavor_game);
		virtual ~GameServer();
		void run();
		char* receive(Poco::Net::StreamSocket* connection);
		void send(Poco::Net::StreamSocket* connection);
};

#endif

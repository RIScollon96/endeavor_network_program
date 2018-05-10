#if !defined GAME_CLIENT
#define GAME_CLIENT

#include "Poco/Net/StreamSocket.h"
#include "Poco/Runnable.h"
#include "Poco/Thread.h"
#include "EndeavorGame.h"

#include "String_.h"

class NetworkUtils;
class GameClient : public Poco::Runnable
{
   private:
		int client_id;
		Poco::Net::StreamSocket* connection; 
		Poco::Thread* client_thread;
		EndeavorGame* endeavorGame;
		

   public:
		GameClient(std::string ip_address, int port_num, EndeavorGame* endeavor_game);
		virtual ~GameClient();
		void run();
		char* receive(Poco::Net::StreamSocket* connection);
		void send(Poco::Net::StreamSocket* connection);
};

#endif

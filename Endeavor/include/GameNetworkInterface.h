#ifndef GAME_NETWORK_INTERFACE
#define GAME_NETWORK_INTERFACE

#include "String_.h"

class GameNetworkInterface
{
   private:

   public:
      	GameNetworkInterface() {};
      	virtual ~GameNetworkInterface() {};
	  
      	virtual CSC2110::String getGameState() = 0;
      	virtual void setGameState(CSC2110::String& game_state) = 0;
	  
		virtual int getPlayerID() = 0;   //figure out whose turn it is (the active player)
		virtual void repaint() = 0;      //make sure the new state is drawn
		virtual bool isGameOver() = 0;   //all players should be disabled
		virtual void disableGame() = 0;  //called when not the current player's turn
};

#endif
#if !defined ENDEAVOR_GAME_OVER_STATE
#define ENDEAVOR_GAME_OVER_STATE

#include "EndeavorState.h"
class EndeavorGame;

class GameOverState : public EndeavorState
{
   private:
      EndeavorGame* endeavor_game;

   public:
      GameOverState(EndeavorGame* endeavor_game, CSC2110::String* key);
      virtual ~GameOverState();

      virtual void mouseClicked(uint32 x, uint32 y);
};

#endif

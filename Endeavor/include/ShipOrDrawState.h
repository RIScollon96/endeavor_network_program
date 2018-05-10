#if !defined ENDEAVOR_SHIP_OR_DRAW_STATE
#define ENDEAVOR_SHIP_OR_DRAW_STATE

#include "EndeavorState.h"
class EndeavorGame;

class ShipOrDrawState : public EndeavorState
{
   private:
      EndeavorGame* endeavor_game;

   public:
      ShipOrDrawState(EndeavorGame* endeavor_game, CSC2110::String* key);
      virtual ~ShipOrDrawState();

      virtual void mouseClicked(uint32 x, uint32 y);
};

#endif

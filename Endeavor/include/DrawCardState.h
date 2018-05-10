#if !defined ENDEAVOR_DRAW_CARD_STATE
#define ENDEAVOR_DRAW_CARD_STATE

#include "EndeavorState.h"
class EndeavorGame;

class DrawCardState : public EndeavorState
{
   private:
      EndeavorGame* endeavor_game;

   public:
      DrawCardState(EndeavorGame* endeavor_game, CSC2110::String* key);
      virtual ~DrawCardState();

      virtual void mouseClicked(uint32 x, uint32 y);
};

#endif

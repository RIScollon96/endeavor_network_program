#if !defined ENDEAVOR_OCCUPY_OR_DRAW_STATE
#define ENDEAVOR_OCCUPY_OR_DRAW_STATE

#include "EndeavorState.h"
class EndeavorGame;

class OccupyOrDrawState : public EndeavorState
{
   private:
      EndeavorGame* endeavor_game;

   public:
      OccupyOrDrawState(EndeavorGame* endeavor_game, CSC2110::String* key);
      virtual ~OccupyOrDrawState();

      virtual void mouseClicked(uint32 x, uint32 y);
};

#endif

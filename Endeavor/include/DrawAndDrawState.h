#if !defined ENDEAVOR_DRAW_AND_DRAW_STATE
#define ENDEAVOR_DRAW_AND_DRAW_STATE

#include "EndeavorState.h"
class EndeavorGame;

class DrawAndDrawState : public EndeavorState
{
   private:
      EndeavorGame* endeavor_game;
	  
	  EndeavorRegionType action_region;
	  bool first_draw;
	  bool second_draw;

   public:
      DrawAndDrawState(EndeavorGame* endeavor_game, CSC2110::String* key);
      virtual ~DrawAndDrawState();

      virtual void mouseClicked(uint32 x, uint32 y);
};

#endif

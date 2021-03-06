#if !defined ENDEAVOR_OCCUPY_STATE
#define ENDEAVOR_OCCUPY_STATE

#include "EndeavorState.h"
class EndeavorGame;

class OccupyState : public EndeavorState
{
   private:
      EndeavorGame* endeavor_game;

   public:
      OccupyState(EndeavorGame* endeavor_game, CSC2110::String* key);
      virtual ~OccupyState();

      virtual void mouseClicked(uint32 x, uint32 y);
};

#endif

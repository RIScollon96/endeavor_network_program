#if !defined ENDEAVOR_SHIP_AND_OCCUPY_STATE
#define ENDEAVOR_SHIP_AND_OCCUPY_STATE

#include "EndeavorState.h"
class EndeavorGame;

class ShipAndOccupyState : public EndeavorState
{
   private:
      EndeavorGame* endeavor_game;
	  
	  EndeavorRegionType action_region;
	  bool ship;
	  bool occupy;

   public:
      ShipAndOccupyState(EndeavorGame* endeavor_game, CSC2110::String* key);
      virtual ~ShipAndOccupyState();

      virtual void mouseClicked(uint32 x, uint32 y);
};

#endif

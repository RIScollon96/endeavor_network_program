#if !defined ENDEAVOR_SHIP_AND_SHIP_STATE
#define ENDEAVOR_SHIP_AND_SHIP_STATE

#include "EndeavorState.h"
class EndeavorGame;

class ShipAndShipState : public EndeavorState
{
   private:
      EndeavorGame* endeavor_game;
	  
	  EndeavorRegionType action_region;
	  bool first_ship;
	  bool second_ship;

   public:
      ShipAndShipState(EndeavorGame* endeavor_game, CSC2110::String* key);
      virtual ~ShipAndShipState();

      virtual void mouseClicked(uint32 x, uint32 y);
};

#endif

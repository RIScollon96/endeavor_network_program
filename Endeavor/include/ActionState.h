#if !defined ENDEAVOR_ACTION_STATE
#define ENDEAVOR_ACTION_STATE

#include "EndeavorState.h"
class EndeavorGame;

class ActionState : public EndeavorState
{
	private:
		EndeavorGame* endeavor_game;

	public:
		ActionState(EndeavorGame* endeavor_game, CSC2110::String* key);
		virtual ~ActionState();

		virtual void mouseClicked(uint32 x, uint32 y);
};

#endif

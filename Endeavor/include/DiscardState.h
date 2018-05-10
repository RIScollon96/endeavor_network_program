#if !defined ENDEAVOR_DISCARD_STATE
#define ENDEAVOR_DISCARD_STATE

#include "EndeavorState.h"
class EndeavorGame;

class DiscardState : public EndeavorState
{
	private:
		EndeavorGame* endeavor_game;

	public:
		DiscardState(EndeavorGame* endeavor_game, CSC2110::String* key);
		virtual ~DiscardState();

		virtual void mouseClicked(uint32 x, uint32 y);
};

#endif

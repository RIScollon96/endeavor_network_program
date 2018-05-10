#if !defined ENDEAVOR_ATTACK_STATE
#define ENDEAVOR_ATTACK_STATE

#include "EndeavorState.h"
class EndeavorGame;

class AttackState : public EndeavorState
{
   private:
      EndeavorGame* endeavor_game;

   public:
      AttackState(EndeavorGame* endeavor_game, CSC2110::String* key);
      virtual ~AttackState();

      virtual void mouseClicked(uint32 x, uint32 y);
};

#endif

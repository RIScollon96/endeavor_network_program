#include "AttackState.h"
#include "EndeavorGame.h"

AttackState::AttackState(EndeavorGame* game, CSC2110::String* key) : EndeavorState(key)
{
	endeavor_game = game;
}

AttackState::~AttackState()
{}

void AttackState::mouseClicked(uint32 x, uint32 y)
{
	uint8 active_player = endeavor_game->getActivePlayer();

	uint8 city_id = endeavor_game->findSelectedCity(x, y);  
	if (city_id == 0) return;
	
	if (!endeavor_game->canAttackCity(active_player, city_id)) return;

	endeavor_game->attackCity(active_player, city_id);
   
	endeavor_game->nextPlayer();  //player has not passed yet (took an action)
	endeavor_game->changeToActionState();

}

#include "GameOverState.h"
#include "EndeavorGame.h"

GameOverState::GameOverState(EndeavorGame* game, CSC2110::String* key) : EndeavorState(key)
{
	endeavor_game = game;
}

GameOverState::~GameOverState()
{}

void GameOverState::mouseClicked(uint32 x, uint32 y)
{

}

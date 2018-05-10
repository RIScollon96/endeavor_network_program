#include "EndeavorState.h"

EndeavorState::EndeavorState(CSC2110::String* key)
{
	state_key = key;
}

EndeavorState::~EndeavorState()
{
	delete state_key;
}

CSC2110::String* EndeavorState::getKey()
{
	return state_key;
}

int EndeavorState::computeHashFunctionState(EndeavorState* state)
{
	return computeHashFunctionKey(state->getKey());
}

int EndeavorState::computeHashFunctionKey(CSC2110::String* key)
{
	return key->computeHashFunctionByASCIISum();
}

int EndeavorState::compareStates(EndeavorState* state_1, EndeavorState* state_2)
{
	CSC2110::String* key_1 = state_1->getKey();
	CSC2110::String* key_2 = state_2->getKey();
	return key_1->compare(key_2);
}

int EndeavorState::compareStatesByKeyAndState(CSC2110::String* key_1, EndeavorState* state)
{
	CSC2110::String* key_2 = state->getKey();
	return key_1->compare(key_2);
}

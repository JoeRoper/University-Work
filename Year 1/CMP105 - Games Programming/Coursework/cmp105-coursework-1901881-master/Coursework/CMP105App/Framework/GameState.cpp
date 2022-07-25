#include "GameState.h"

// Set the current state
void GameState::setCurrentState(State s)
{
	currentState = s;
}

// Set the last state
void GameState::setLastState(State s)
{
	lastState = s;
}

// Returns the current state.
State GameState::getCurrentState()
{
	return currentState;
}

State GameState::getLastState()
{
	return lastState;
}

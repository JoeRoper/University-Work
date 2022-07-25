// Game State Class
// Simple game state controller. enum lists possible game states (can be modified), tracks and updates the current state
// @author Paul Robertson

#pragma once

// Possible states. This enum can be modified to add additional states as required.
enum class State { MENU, LEVEL, PAUSE, RESTART, STORY, CONTROLS, WIN, DEATH };

class GameState
{
public:
	// Set the current state
	void setCurrentState(State s);
	// Set the last state
	void setLastState(State s);
	// Returns the current state.
	State getCurrentState();
	// Returns the last state state.
	State getLastState();


protected:
	State currentState;
	State lastState;
};
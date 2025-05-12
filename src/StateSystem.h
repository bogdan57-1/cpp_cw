#pragma once
#include "header.h"
#include "StartScreenState.h"

class PlayGameState;

class StateSystem
{
protected:
	State* m_currentState = nullptr;
	PlayGameState* playGameBackup = nullptr;
	SpaceInvadersEngine* m_pEngine;

public:
	StateSystem(SpaceInvadersEngine* engine) :
		m_pEngine(engine)
	{
		//Set initial state
		m_currentState = new StartScreenState(m_pEngine, this);
	};
	~StateSystem();

	void setState(State* state);
	void setupBackgroundBuffer();
	void handleMouseDown(int iButton, int iX, int iY);
	void mainLoopPreUpdate();
	void mainLoopDoAfterUpdate();
	void createSurfaces();
	int initialiseObjects();
	void restorePlayState();
	void copyAllBackgroundBuffer();
	void keyDown(int iKeyCode);
	PixelTileManager* getTileManager();


	void testClass() { std::cout << "STATE SYSTEM IS PRESENT" << std::endl; };


};


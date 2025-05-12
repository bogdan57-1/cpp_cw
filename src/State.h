#pragma once
#include "header.h"

class SpaceInvadersEngine;
class StateSystem;
class PixelTileManager;


class State
{
protected:
	SpaceInvadersEngine* m_pEngine;
	StateSystem* m_pStateSystem;

public:
	State(SpaceInvadersEngine* engine, StateSystem* stateSystem) :
		m_pEngine(engine),
		m_pStateSystem(stateSystem)
	{};

	virtual ~State() {}; //this made me question my sanity for a whole day because it wasnt virtual

	virtual void setupBackgroundBuffer();
	virtual void handleMouseDown(int iButton, int iX, int iY);
	virtual void mainLoopPreUpdate();
	virtual void createSurfaces();
	virtual int initialiseObjects();
	virtual void mainLoopDoAfterUpdate();
	virtual void copyAllBackgroundBuffer();
	virtual void keyDown(int iKeyCode);
	virtual PixelTileManager* getTileManager();

};


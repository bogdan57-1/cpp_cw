#include "header.h"
#include "PauseState.h"
#include "StateSystem.h"
#include "SpaceInvadersEngine.h"
#include "PlayGameState.h"
#include "StateSystem.h"
#include "DrawingSurface.h"

PauseState::PauseState(SpaceInvadersEngine* engine, StateSystem* stateSystem)
	: State(engine, stateSystem),
	pauseBackground(DrawingSurface(engine))
{
	//Backup Background
	previousBackground = engine->getBackgroundSurface();

	//Initialise surface
	pauseBackground.createSurface(engine->getWindowWidth(), engine->getWindowHeight());

	engine->setBackgroundSurface(&pauseBackground);

	//Hide objects
	engine->setAllObjectsVisible(false);
}

PauseState::~PauseState()
{
	std::cout << "delete pause state" << std::endl;
}



void PauseState::setupBackgroundBuffer()
{
	m_pEngine->lockBackgroundForDrawing();

	m_pEngine->getBackgroundSurface()->fillSurface(0xD6D6D6);

	SDL_Color color = { (Uint8)((0xffffff & 0xff0000) >> 16), (Uint8)((0xffffff & 0xff00) >> 8), (Uint8)((0xffffff & 0xff)), 0 };
	SDL_Surface* sText = TTF_RenderText_Solid(m_pEngine->getDefaultFont()->getTTFFont(), "Game is Paused", color);

	m_pEngine->drawBackgroundString(
		m_pEngine->getWindowWidth()/2 - sText->w / 2,
		m_pEngine->getWindowHeight()/2 - sText->h / 2,
		"Game is Paused", 0xffffff);

	m_pEngine->redrawDisplay();
	
}

void PauseState::createSurfaces()
{
	//Surfaces are already created when starting the game
	//Do nothing
}

int PauseState::initialiseObjects()
{
	//pause state can only be reached from PlayGameState
	//do not change the array of objects since they are still in the containter
	return 0;
}

void PauseState::keyDown(int iKeyCode)
{
	if (iKeyCode == SDLK_ESCAPE) {
		//First restore background
		m_pEngine->setBackgroundSurface(previousBackground);
		//Then unpause
		m_pEngine->unpause();
		//Make objects visible again
		m_pEngine->setAllObjectsVisible(true);
		//Pause state will be deleted after this call
		m_pStateSystem->restorePlayState();
	}
}

void PauseState::mainLoopPreUpdate()
{
	m_pEngine->redrawDisplay();
}

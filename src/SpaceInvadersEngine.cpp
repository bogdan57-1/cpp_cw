#include "header.h"
#include "SpaceInvadersEngine.h"
#include "StateSystem.h"

SpaceInvadersEngine::SpaceInvadersEngine()
{
	//Create state manager
	m_stateSystem = std::make_shared<StateSystem>(this);
}

SpaceInvadersEngine::~SpaceInvadersEngine()
{
	m_stateSystem.reset();
}

void SpaceInvadersEngine::virtSetupBackgroundBuffer()
{

	m_stateSystem->setupBackgroundBuffer();
}

void SpaceInvadersEngine::virtDrawStringsOnTop()
{

}

void SpaceInvadersEngine::virtMouseDown(int iButton, int iX, int iY)
{	
	m_stateSystem->handleMouseDown(iButton, iX, iY);
}

int SpaceInvadersEngine::virtInitialise()
{
	// Set up the initial background
	m_pBackgroundSurface->mySDLLockSurface();
	virtSetupBackgroundBuffer();
	m_pBackgroundSurface->mySDLUnlockSurface();

	// Create the moving objects
	virtInitialiseObjects();

	return 0; // success
}

void SpaceInvadersEngine::virtMainLoopPreUpdate()
{
	m_stateSystem->mainLoopPreUpdate();
}



void SpaceInvadersEngine::setBackgroundSurface(DrawingSurface* newSurface)
{
	if (newSurface) {
		m_pBackgroundSurface = newSurface;
	}
}

PixelTileManager* SpaceInvadersEngine::getTileManager()
{
	return m_stateSystem->getTileManager();
}

void SpaceInvadersEngine::virtCreateSurfaces()
{
	m_stateSystem->createSurfaces();
}

int SpaceInvadersEngine::virtInitialiseObjects()
{
	return m_stateSystem->initialiseObjects(); 
}

void SpaceInvadersEngine::virtMainLoopDoAfterUpdate()
{
	m_stateSystem->mainLoopDoAfterUpdate();
}

void SpaceInvadersEngine::copyAllBackgroundBuffer()
{
	m_stateSystem->copyAllBackgroundBuffer();
}

void SpaceInvadersEngine::virtKeyDown(int iKeyCode)
{
	m_stateSystem->keyDown(iKeyCode);
}


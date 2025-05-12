#include "header.h"
#include "State.h"
#include "SpaceInvadersEngine.h"
#include "PixelTileManager.h"


//Set defaults so that subclasses only override what is necessary

void State::setupBackgroundBuffer()
{
	m_pEngine->BaseEngine::virtSetupBackgroundBuffer();
}

void State::handleMouseDown(int iButton, int iX, int iY)
{
	m_pEngine->BaseEngine::virtMouseDown(iButton, iX, iY);
}

void State::mainLoopPreUpdate()
{
	m_pEngine->BaseEngine::virtMainLoopPreUpdate();
}

void State::createSurfaces() {
	m_pEngine->BaseEngine::virtCreateSurfaces();
}

int State::initialiseObjects() {
	return m_pEngine->BaseEngine::virtInitialiseObjects();
}

void State::mainLoopDoAfterUpdate()
{
	m_pEngine->BaseEngine::virtMainLoopDoAfterUpdate();
}

void State::copyAllBackgroundBuffer()
{
	m_pEngine->BaseEngine::copyAllBackgroundBuffer();
}

void State::keyDown(int iKeyCode)
{
	m_pEngine->BaseEngine::virtKeyDown(iKeyCode);
}

PixelTileManager* State::getTileManager()
{
	return nullptr;
}

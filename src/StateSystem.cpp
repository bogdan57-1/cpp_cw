#include "header.h"
#include "StateSystem.h"
#include "SpaceInvadersEngine.h"
#include "PlayGameState.h"

StateSystem::~StateSystem() {
	//hook up here to save the game

	//free the contained state
	if (m_currentState) {
		delete m_currentState;
	}
	if (playGameBackup && m_currentState != (State*)playGameBackup) {
		//could hook up here to save the state of the game. (problem if currentState was playGame)
		delete playGameBackup;
	}
}

void StateSystem::setState(State* state)
{
	//Check if the state is the play game state
	if (dynamic_cast<PlayGameState*>(state) != nullptr) {
		//Updates when changing to a playGameState the first time
		if(playGameBackup == nullptr)
			playGameBackup = dynamic_cast<PlayGameState*>(state);
	}

	//std::cout << "CHANGING STATE" << std::endl;
	//free memory for previous state
	//do not free memory for the playState yet
	if (m_currentState != nullptr && dynamic_cast<PlayGameState*>(m_currentState) == nullptr) {
		//std::cout << "DETELE PREVIOUS STATE" << std::endl;
		delete m_currentState; //calls destructor
	}

	this->m_currentState = state;

	m_pEngine->virtCreateSurfaces();
	m_pEngine->virtInitialise();
}

void StateSystem::restorePlayState() {
	//A bit awkward to do this here but you have to free the pause state
	delete m_currentState;

	//No need to initialise again since the play state should be ready
	if (playGameBackup != nullptr)
		this->m_currentState = playGameBackup;
	else
		std::cout << "Could not restore null play state." << std::endl;

}

void StateSystem::copyAllBackgroundBuffer()
{
	m_currentState->copyAllBackgroundBuffer();
}

void StateSystem::keyDown(int iKeyCode)
{
	m_currentState->keyDown(iKeyCode);
}

void StateSystem::setupBackgroundBuffer()
{
	m_currentState->setupBackgroundBuffer();
}

void StateSystem::handleMouseDown(int iButton, int iX, int iY)
{
	m_currentState->handleMouseDown(iButton, iX, iY);
}

void StateSystem::mainLoopPreUpdate()
{
	m_currentState->mainLoopPreUpdate();
}	

void StateSystem::mainLoopDoAfterUpdate()
{
	m_currentState->mainLoopDoAfterUpdate();
}

void StateSystem::createSurfaces()
{
	m_currentState->createSurfaces();
}

int StateSystem::initialiseObjects()
{
	return m_currentState->initialiseObjects();
}


PixelTileManager* StateSystem::getTileManager()
{
	return m_currentState->getTileManager();
}

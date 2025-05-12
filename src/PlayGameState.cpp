#include "header.h"
#include "State.h"
#include "PlayGameState.h"
#include "SpaceInvadersEngine.h"
#include "StateSystem.h"
#include "PauseState.h"
#include "Projectile.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "PlayerShip.h"

PlayGameState::PlayGameState(SpaceInvadersEngine* engine, StateSystem* stateSystem)
	: State(engine, stateSystem)
{
	//Load Textures
	backgroundBase = ImageManager::loadImage("resources/SpaceShooterRedux/PNG/bkgd_0_resized.png");
	backgroundOverlay = ImageManager::loadImage("resources/SpaceShooterRedux/PNG/starsOverlay_resized.png");
	backgroundOverlay.setTransparencyColour(0x000000);

	//Set offset
	overlayOffset = 0;
}

void PlayGameState::setupBackgroundBuffer()
{
	m_pEngine->lockBackgroundForDrawing();
	m_pEngine->fillBackground(0x000040);

	backgroundBase.renderImage(m_pEngine->getBackgroundSurface(),
		0, 0, 
		0, 0, 
		m_pEngine->getWindowWidth(), m_pEngine->getWindowHeight());

	m_pEngine->unlockBackgroundForDrawing();

}

void PlayGameState::createSurfaces()
{
	//Follows after start screen state, so the surfaces are already initialised
	//do nothing;
}

int PlayGameState::initialiseObjects()
{
	m_pEngine->drawableObjectsChanged();

	m_pEngine->destroyOldObjects(true);

	m_pEngine->createObjectArray(2);

	//Create the player ship
	SimpleImage playerTexture = ImageManager::loadImage("resources/SpaceShooterRedux/PNG/playerShip1_blue.png");
	PlayerShip* playerShip = new PlayerShip(m_pEngine, playerTexture, playerTexture.getWidth(), playerTexture.getHeight());
	m_pEngine->storeObjectInArray(0, playerShip);

	//Add dummy enemy
	Enemy* enemy = EnemyManager::createEnemy(m_pEngine, BASIC_ENEMY, 100, 100);
	m_pEngine->storeObjectInArray(1, enemy);

	m_pEngine->setAllObjectsVisible(true);

	return 0;
}

void PlayGameState::mainLoopDoAfterUpdate()
{
	//Destroy required projectiles
	DisplayableObject* pObject = NULL;
	for (int objID = 0; (pObject = m_pEngine->getDisplayableObject(objID)) != NULL; objID++) {
		pObject = dynamic_cast<Projectile*>(pObject);
		if (pObject) {
			//object is a projectile
			if (((Projectile*)pObject)->toBeRemoved() || ((Projectile*)pObject)->hasHit()) {
				//std::cout << "Projectile Removed and deleted;" << std::endl;
				m_pEngine->removeDisplayableObject(pObject);
				delete pObject;
			}
		}
	}


	//Check if the player has died


	//Destroy killed enemies
	//Also check if no enemies are left for win condition

}

void PlayGameState::mainLoopPreUpdate()
{
	//Handles incrementing the offset of the overlay
	overlayUpdateCounter = (overlayUpdateCounter + 1) % OVERLAY_UPDATE_PERIOD;
	if(overlayUpdateCounter == 0)
		overlayOffset = (overlayOffset + 1) % backgroundOverlay.getHeight();
	m_pEngine->redrawDisplay();
}

void PlayGameState::copyAllBackgroundBuffer()
{
	//First copy the background simply
	m_pEngine->getForegroundSurface()->copyEntireSurface(m_pEngine->getBackgroundSurface());

	//Then render the stars with an offset
	m_pEngine->redrawRectangle(0, 0, m_pEngine->getWindowWidth(), m_pEngine->getWindowHeight());

	//copy top part of image moving downwards
	backgroundOverlay.renderImageBlit(m_pEngine, m_pEngine->getForegroundSurface(),
		0, overlayOffset, //xy location
		m_pEngine->getWindowWidth(), m_pEngine->getWindowHeight() - overlayOffset, //target width height
		0, 0, //xy top left in image
		backgroundOverlay.getWidth(), backgroundOverlay.getHeight() - overlayOffset); //image width height

	//copy bottom part of image above
	backgroundOverlay.renderImageBlit(m_pEngine, m_pEngine->getForegroundSurface(),
		0, 0, //xy location
		m_pEngine->getWindowWidth(), overlayOffset, //target width height
		0, backgroundOverlay.getHeight()-overlayOffset, //xy top left in image
		backgroundOverlay.getWidth(), overlayOffset); //image width height
}

void PlayGameState::keyDown(int iKeyCode)
{
	//std::cout << "KEY CODE: " << iKeyCode << std::endl;
	if (iKeyCode == SDLK_ESCAPE) {
		//First pause the time
		m_pEngine->pause();
		m_pStateSystem->setState(new PauseState(m_pEngine, m_pStateSystem));
	}
}

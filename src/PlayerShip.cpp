#include "PlayerShip.h"
#include "SpaceInvadersEngine.h"
#include "Utility.h"
#include "ProjectileManager.h"
#include "Projectile.h"

PlayerShip::PlayerShip(BaseEngine* engine, SimpleImage texture, int width, int height)
	:DisplayableObject(engine, width, height, false)
{
	this->texture = texture;
	m_iCurrentScreenX = m_pEngine->getWindowWidth() / 2;
	//m_iCurrentScreenY = m_pEngine->getWindowHeight() - texture.getHeight()/2 - 15;
	m_iCurrentScreenY = 920;

	/*for (int i = 1; i <= 7; i++) {
		std::string path = "resources/SpaceShooterRedux/PNG/Effects/fire1";
		path = path + std::to_string(i) + ".png";
		fireTrail[i-1] = ImageManager::loadImage(path);
	}*/
	fireTrail[0] = ImageManager::loadImage("resources/SpaceShooterRedux/PNG/Effects/fire13.png");
	fireTrail[1] = ImageManager::loadImage("resources/SpaceShooterRedux/PNG/Effects/fire16.png");
	fireTrail[2] = ImageManager::loadImage("resources/SpaceShooterRedux/PNG/Effects/fire17.png");
	fireTrailIndex = 0;
	fireTrailLastUpdate = 0;

	//Set firing cooldown
	shootCooldown = 0;
}

void PlayerShip::virtDraw()
{
	if (isVisible()) {
		//renders it with the centre at currentX, currentY
		texture.renderImageWithMask(m_pEngine->getForegroundSurface(),
			0, 0, this->getDrawingRegionLeft(), this->getDrawingRegionTop(),
			texture.getWidth(), texture.getHeight());
		/*texture.renderImageBlit(m_pEngine, m_pEngine->getForegroundSurface(),
			0, 0, this->getDrawingRegionLeft(), this->getDrawingRegionTop(),
			0,0,texture.getWidth(), texture.getHeight());*/

		fireTrail[fireTrailIndex].renderImageWithMaskAndTransparency(m_pEngine->getForegroundSurface(),
			0,0, getXCentre() - fireTrail[fireTrailIndex].getWidth()/2, getYCentre() + getDrawHeight()/2 + 5,
			fireTrail[fireTrailIndex].getWidth(), fireTrail[fireTrailIndex].getHeight(), 0x000000, 100);


		//Visual effects
		int currentTime = m_pEngine->getModifiedTime();
		if (currentTime - fireTrailLastUpdate > rand() % 300) {
			if (fireTrailIndex == 2) {
				if(rand()%50 > 30)
					fireTrailIndex = (fireTrailIndex + 1) % 3;
			}
			else 
				fireTrailIndex = (fireTrailIndex + 1) % 3;
			fireTrailLastUpdate = currentTime;
		}
	}
	
}

void PlayerShip::virtDoUpdate(int iCurrentTime)
{
	if (!m_pEngine->isPaused()) {
		//Move
		int offset = 5;
		if (getEngine()->isKeyPressed(SDLK_LEFT))
		{
			if (getDrawingRegionLeft() - offset >= 0)
				m_iCurrentScreenX -= offset;
			else
				m_iCurrentScreenX -= getDrawingRegionLeft();
		}
		if (getEngine()->isKeyPressed(SDLK_RIGHT))
		{
			if (getDrawingRegionRight() + offset <= m_pEngine->getWindowWidth())
				m_iCurrentScreenX += offset;
			else
				m_iCurrentScreenX += m_pEngine->getWindowWidth() - getDrawingRegionRight();
		}

		//Shoot
		if (shootCooldown > 0) shootCooldown--;
		if (getEngine()->isKeyPressed(SDLK_SPACE) && shootCooldown==0) {
			shootCooldown = 10;
			Projectile* proj = ProjectileManager::createProjectile(
				getEngine(), BASIC_PROJECTILE, getXCentre(), getDrawingRegionTop() - BASIC_PROJECTILE_HEIGHT/2 - 5, FIRED_BY_PLAYER); //some padding
			proj->setSpeed(0, -5);
			getEngine()->appendObjectToArray(proj);
		}
	}
}

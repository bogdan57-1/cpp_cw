#include "header.h"
#include "SpaceInvadersEngine.h"
#include "Projectile.h"
#include "Particle.h"
#include "PlayerShip.h"
#include "Enemy.h"
#include "PixelCollisionUtility.h"

Projectile::Projectile(BaseEngine* engine, SimpleImage texture, int width, int height, int initialX, int initialY)
	: DisplayableObject(engine, width, height, false)
{
	this->texture = texture;
	m_iCurrentScreenX = initialX;
	m_iCurrentScreenY = initialY;

	lastTrailTime = 0;
}

Projectile::~Projectile()
{
	//free particles memory
	for (Particle* pcl : particleTrail) {
		delete pcl;
	}
}

void Projectile::virtDraw()
{
	if (isVisible()) {
		//renders with center at currentX, currentY
		texture.renderImageWithMask(m_pEngine->getForegroundSurface(),
			0, 0, this->getDrawingRegionLeft(), this->getDrawingRegionTop(),
			texture.getWidth(), texture.getHeight());

		//Draw particles
		//Projectile is responsible for drawing its particles
		for (auto pcl : particleTrail) {
			pcl->drawToForeground();
		}
	}

}

void Projectile::virtDoUpdate(int iCurrentTime)
{
	if (!m_pEngine->isPaused()) {
		//Check collision
		//Can collide with enemies and player
		//Therefore make sure that a generated projectile is generated "ahead" of the object

		DisplayableObject* pObject = NULL;
		PlayerShip* pPlayer = NULL;
		Enemy* pEnemy = NULL;
		for (int objID = 0; (pObject = m_pEngine->getDisplayableObject(objID)) != NULL; objID++) {
			//Not itself
			//if (pObject == this) continue;
			//Not a projectile -> includes itself i guess
			if (dynamic_cast<Projectile*>(pObject)) continue;

			pPlayer = dynamic_cast<PlayerShip*>(pObject);
			if (pPlayer && !isPlayerFriendly) {
				//if the object is a player

			}
			//std::cout << "damage value:" << damageValue << std::endl;
			pEnemy = dynamic_cast<Enemy*>(pObject);
			if (pEnemy && !isEnemyFriendly) {
				//if the object is an enemy
				if (PixelCollisionUtility<Enemy>::existsCollision(this, pEnemy)) {
					this->speedY = 0;
					this->flagHasHit = true;
				}
			}
		}

		//Move
		m_iCurrentScreenX += speedX;
		m_iCurrentScreenY += speedY;

		//Check bounds
		if (getDrawingRegionBottom() < 0 || getDrawingRegionTop() > m_pEngine->getWindowHeight() ||
			getDrawingRegionRight() < 0 || getDrawingRegionLeft() > m_pEngine->getWindowWidth()) {
			flagToBeRemoved = true;
		}

		//Create trail
		double radius = getDrawWidth() * 0.5;
		int time = m_pEngine->getModifiedTime();
		if (time - lastTrailTime > 30) {
			lastTrailTime = time;
			for (int i = 0; i < rand() % 4; i++) {
				particleTrail.push_back(new Particle(m_pEngine, getXCentre() + (rand()%10/10.0)*radius*(rand()%3-1), getDrawingRegionBottom(), 0x00ff00, 30));
			}
		}
		//Destroy old particles
		//The projectile is responsible for its own particles
		for (int i = 0; i < particleTrail.size(); i++) {
			Particle* pcl = particleTrail[i];
			pcl->updateLifetime();
			if (!pcl->isAlive()) {
				particleTrail.erase(particleTrail.begin() + i);
				delete pcl;
			}
		}

	}


}
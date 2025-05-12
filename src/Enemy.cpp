#include "header.h"
#include "SpaceInvadersEngine.h"
#include "Enemy.h"

Enemy::Enemy(BaseEngine* engine, SimpleImage texture, int width, int height, int initialX, int initialY)
	: DisplayableObject(engine, width, height, false)
{
	this->texture = texture;
	m_iCurrentScreenX = initialX;
	m_iCurrentScreenY = initialY;
}

void Enemy::virtDraw()
{
	if (isVisible()) {
		//renders with center at currentX, currentY
		texture.renderImageWithMask(m_pEngine->getForegroundSurface(),
			0, 0, this->getDrawingRegionLeft(), this->getDrawingRegionTop(),
			texture.getWidth(), texture.getHeight());
	}
}

void Enemy::virtDoUpdate(int iCurrentTime)
{
	//if is not paused
	DisplayableObject::virtDoUpdate(iCurrentTime);
}

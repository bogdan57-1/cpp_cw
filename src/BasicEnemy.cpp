#include "BasicEnemy.h"
#include "ProjectileManager.h"

BasicEnemy::BasicEnemy(BaseEngine* engine, SimpleImage texture, int width, int height, int initialX, int initialY)
	: Enemy(engine, texture, width, height, initialX, initialY)
{
	projectileType = BASIC_PROJECTILE;
}

void BasicEnemy::virtDoUpdate(int iCurrentTime)
{
	//if is not paused
}

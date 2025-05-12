#include "BasicProjectile.h"

BasicProjectile::BasicProjectile(BaseEngine* engine, SimpleImage texture, int width, int height, int initialX, int initialY)
	: Projectile(engine, texture, width, height, initialX, initialY)
{
	this->damageValue = 3;

}

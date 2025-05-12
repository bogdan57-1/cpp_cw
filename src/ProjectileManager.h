#pragma once

class Projectile;

#define BASIC_PROJECTILE 0
#define BASIC_PROJECTILE_HEIGHT 37


#define FIRED_BY_PLAYER 0
#define FIRED_BY_ENEMY 1
#define FIRED_BY_OTHER 2

class ProjectileManager
{
public:
	ProjectileManager() = delete;

	static Projectile* createProjectile(BaseEngine* engine, int projectileType, int initialX, int initialY, int firedBy);
};


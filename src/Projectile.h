#pragma once
#include "DisplayableObject.h"
#include "SimpleImage.h"
#include <vector>

class Particle;

class Projectile
	: public DisplayableObject
{

	friend class ProjectileManager;
	
public:
	Projectile(BaseEngine* engine, SimpleImage texture, int width, int height, int initialX, int initialY);
	~Projectile();

	void virtDraw() override;
	void virtDoUpdate(int iCurrentTime) override;

	double inline getUnitSpeed() { return unitSpeed; }
	void inline setSpeed(int speedX, int speedY) { this->speedX = speedX; this->speedY = speedY; }
	bool inline toBeRemoved() { return flagToBeRemoved; }
	bool inline hasHit() { return flagHasHit; }

	inline SimpleImage const* getTexture() { return &texture; };

	//Gameplay
	inline double getDamageValue() { return damageValue; };

protected:
	bool flagHasHit = false;
	bool flagToBeRemoved = false;
	SimpleImage texture;

	int speedX = 0;
	int speedY = 0;

	//length of the speed vector to compute x and y speed
	double unitSpeed;

	std::vector<Particle*> particleTrail;
	int lastTrailTime;

	//Gameplay mechanics
	bool isPlayerFriendly = false;
	bool isEnemyFriendly = false;
	double damageValue;

};


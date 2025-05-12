#include "Particle.h"
#include "SpaceInvadersEngine.h"

#define SIZE_CONSTANT 0.3
#define HALFLIFE_CONSTANT 1

Particle::Particle(BaseEngine* engine, int x, int y, int colour, int lifetime)
	: m_pEngine(engine), x(x), y(y), colour(colour), lifetime(lifetime)
{
	size = lifetime * SIZE_CONSTANT;
}

void Particle::drawToForeground()
{
	m_pEngine->drawForegroundOval(x-size*0.5, y-size*0.5, x+size*0.5, y+size*0.5, colour);
}

void Particle::updateLifetime()
{
	if(lifetime>0) lifetime-=HALFLIFE_CONSTANT;
	size = lifetime * SIZE_CONSTANT;
}

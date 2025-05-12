#pragma once

class BaseEngine;

class Particle
{
public:
	Particle(BaseEngine* engine ,int x, int y, int colour, int lifetime);

	void drawToForeground();
	void updateLifetime();
	bool inline isAlive() { return (lifetime > 0); }

private:
	BaseEngine* m_pEngine;
	int lifetime;
	int x, y;
	int colour;
	double size;
};


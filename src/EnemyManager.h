#pragma once

#define BASIC_ENEMY 0

class Enemy;
class BaseEngine;

class EnemyManager
{
public:
	EnemyManager() = delete;

	static Enemy* createEnemy(BaseEngine* engine, int enemyType, int initialX, int initialY);

};


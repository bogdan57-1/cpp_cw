#include "header.h"
#include "SpaceInvadersEngine.h"
#include "EnemyManager.h"
#include "Enemy.h"

#include "BasicEnemy.h"

Enemy* EnemyManager::createEnemy(BaseEngine* engine, int enemyType, int initialX, int initialY)
{
    Enemy* enemy = nullptr;
    SimpleImage texture;

    switch (enemyType) {
        case BASIC_ENEMY: {
            texture = ImageManager::loadImage("resources/SpaceShooterRedux/PNG/Enemies/enemyBlack1.png", true);
            enemy = new BasicEnemy(engine, texture, texture.getWidth(), texture.getHeight(), initialX, initialY);
            break;
        }
    }
    return enemy;
}

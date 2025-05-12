#include "header.h"
#include "SpaceInvadersEngine.h"
#include "ProjectileManager.h"

#include "BasicProjectile.h"


Projectile* ProjectileManager::createProjectile(BaseEngine* engine, int projectileType, int initialX, int initialY, int firedBy)
{
    Projectile* projectile = nullptr;
    SimpleImage texture;

    switch (projectileType) {
        case BASIC_PROJECTILE: {
            texture = ImageManager::loadImage("resources/SpaceShooterRedux/PNG/Lasers/laserGreen05.png", true);
            projectile = new BasicProjectile(engine, texture, texture.getWidth(), texture.getHeight(), initialX, initialY);

            break;
        }
    }

    //Set interaction mode - fired by player or other so that it doesnt interact with that faction
    switch (firedBy) {
        case FIRED_BY_PLAYER: {
            projectile->isPlayerFriendly = true;
            break;
        }
        case FIRED_BY_ENEMY: {
            projectile->isEnemyFriendly = true;
            break;
        }
    }

    return projectile;
}
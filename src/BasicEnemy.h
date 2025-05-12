#pragma once
#include "Enemy.h"
class BasicEnemy :
    public Enemy
{
public:
    BasicEnemy(BaseEngine* engine, SimpleImage texture, int width, int height, int initialX, int initialY);

    void virtDoUpdate(int iCurrentTime) override;
};


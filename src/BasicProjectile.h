#pragma once
#include "Projectile.h"
class BasicProjectile :
    public Projectile
{
public:
    BasicProjectile(BaseEngine* engine, SimpleImage texture, int width, int height, int initialX, int initialY);
};


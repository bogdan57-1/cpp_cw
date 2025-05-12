#pragma once
#include "DisplayableObject.h"
#include "SimpleImage.h"
class Enemy :
    public DisplayableObject
{
public:
    Enemy(BaseEngine* engine, SimpleImage texture, int width, int height, int initialX, int initialY);

    void virtDraw() override;
    void virtDoUpdate(int iCurrentTime) override;

    inline SimpleImage const* getTexture() { return &texture; };

protected:
    SimpleImage texture;
    int shootCooldown;
    int projectileType;
};


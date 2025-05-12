#pragma once
#include "DisplayableObject.h"
#include "SimpleImage.h"

class PlayerShip :
    public DisplayableObject
{
public:
    PlayerShip(BaseEngine* engine, SimpleImage texture, int width, int height);

    void virtDraw() override;
    void virtDoUpdate(int iCurrentTime) override;

    inline SimpleImage const* getTexture() { return &texture; };

private:
    SimpleImage texture;
    SimpleImage fireTrail[3];
    int fireTrailIndex;
    int fireTrailLastUpdate;
    int shootCooldown;
};


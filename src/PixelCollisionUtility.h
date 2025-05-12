#pragma once

#include "UtilCollisionDetection.h"

class Projectile;
class DisplayableObject;

template <typename T>
class PixelCollisionUtility
{
public:
	PixelCollisionUtility() = delete;

	static bool existsCollision(Projectile* proj, T* ship) {
        //see if you can use templates for the objects instead

        int projTop = proj->getDrawingRegionTop();
        int projBottom = proj->getDrawingRegionBottom();
        int projLeft = proj->getDrawingRegionLeft();
        int projRight = proj->getDrawingRegionRight();

        int shipTop = ship->getDrawingRegionTop();
        int shipBottom = ship->getDrawingRegionBottom();
        int shipLeft = ship->getDrawingRegionLeft();
        int shipRight = ship->getDrawingRegionRight();

        //right-left = drawWidth and bottom-top = drawHeight

        if (!CollisionDetection::checkRectangles(projLeft, projRight, projTop, projBottom,
            shipLeft, shipRight, shipTop, shipBottom)) {
            //if no rectangle collision, no point in checking bitmaps
            return false;
        }

        //Get textures
        SimpleImage const* projTexture = proj->getTexture();

        SimpleImage const* shipTexture = ship->getTexture();


        //Garbage (it was useful before templating the function):
        /*Enemy* pEnemy = dynamic_cast<Enemy*>(ship);
        PlayerShip* pPlayer = dynamic_cast<PlayerShip*>(ship);
        SimpleImage const* shipTexture = nullptr;
        if (pPlayer)
            shipTexture = pPlayer->getTexture();
        else if (pEnemy)
            shipTexture = pEnemy->getTexture();*/


        //Intersection rectangle coordinates
        int intersectTop = std::max(projTop, shipTop);
        int intersectBottom = std::min(projBottom, shipBottom);
        int intersectLeft = std::max(projLeft, shipLeft);
        int intersectRight = std::min(projRight, shipRight);

        //No need to check for a degenerated rectangle since the collisionDetection function already checks for
        //a proper surface

        int intersectWidth = intersectRight - intersectLeft;
        int intersectHeight = intersectBottom - intersectTop;

        int projOffsetX = intersectLeft - projLeft;
        int projOffsetY = intersectTop - projTop;

        int shipOffsetX = intersectLeft - shipLeft;
        int shipOffsetY = intersectTop - shipTop;

        for (int iX = 0; iX < intersectWidth; iX++) {
            for (int iY = 0; iY < intersectHeight; iY++) {
                int projImageX = iX + projOffsetX;
                int projImageY = iY + projOffsetY;
                int shipImageX = iX + shipOffsetX;
                int shipImageY = iY + shipOffsetY;

                int shipColour = shipTexture->getPixelColour(shipImageX, shipImageY);
                int projColour = projTexture->getPixelColour(projImageX, projImageY);

                //Relies on mask colour being black
                if (shipColour != 0x000000 && projColour != 0x000000) return true;
            }
        }

        return false;
	}
};
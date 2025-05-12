#pragma once
#include "TileManager.h"
class PixelTileManager
    : public TileManager
{
public:
    PixelTileManager(int tileHeight, int tileWidth, int xTiles, int yTiles);

    virtual void virtDrawTileAt(
        BaseEngine* pEngine,
        DrawingSurface* pSurface,
        int iMapX, int iMapY,
        int iStartPositionScreenX, int iStartPositionScreenY) const override;

};
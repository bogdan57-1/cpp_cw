#include "header.h"
#include "PixelTileManager.h"

PixelTileManager::PixelTileManager(int tileHeight, int tileWidth, int xTiles, int yTiles)
	: TileManager(tileHeight, tileWidth, xTiles, yTiles)
{

}

void PixelTileManager::virtDrawTileAt(BaseEngine* pEngine, DrawingSurface* pSurface, int iMapX, int iMapY, int iStartPositionScreenX, int iStartPositionScreenY) const
{
	pSurface->mySDLLockSurface();
	pSurface->drawRectangle(
		iStartPositionScreenX, // Left
		iStartPositionScreenY, // Top
		iStartPositionScreenX + getTileWidth() - 1, // Right
		iStartPositionScreenY + getTileHeight() - 1, // Bottom
		0xff0000);
	pSurface->mySDLUnlockSurface();
}

#pragma once
class BaseEngine;
class DrawingSurface;
class SimpleImage;
class Utility
{
public:
	Utility() = delete;

	static void renderScaledImageWithMask(BaseEngine* pEngine, DrawingSurface* pSurface, SimpleImage img, int xTarget, int yTarget, int xSize, int ySize, double angle);
};


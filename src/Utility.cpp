#include "header.h"
#include "Utility.h"
#include "SimpleImage.h"
#include "SpaceInvadersEngine.h"

// Scale and render an image with a transparency mask.
// The target coordinates are the top-left corner where the drawing will start.
// Size is the size of the area to draw onto.
// Can also rotate image (angle in degrees)
void Utility::renderScaledImageWithMask(BaseEngine* pEngine, DrawingSurface* pSurface, SimpleImage img, int xTarget, int yTarget, int xSize, int ySize, double angle)
{
	int x_max = xTarget + xSize / 2;
	int x_min = xTarget - xSize / 2;
	int y_max = yTarget + ySize / 2;
	int y_min = yTarget - ySize / 2;
	int img_xlen = img.getWidth();
	int img_ylen = img.getHeight();

	auto rawData = img.getRawImageData();
	angle = 2 * M_PI * (angle / 360.0);

	pSurface->mySDLLockSurface();

	double x_a_coef = img_xlen / (double)(x_max - x_min);
	double x_b_coef = -x_a_coef * x_min;
	double y_a_coef = img_ylen / (double)(y_max - y_min);
	double y_b_coef = -y_a_coef * y_min;

	int centerX = x_min + xSize / 2;
	int centerY = y_min + ySize / 2;
	for (int iX = x_min; iX < x_max; iX++) {
		for (int iY = y_min; iY < y_max; iY++) {

			double normalX = iX - centerX;
			double normalY = iY - centerY;

			double rotatedX = normalX * cos(angle) - normalY * sin(angle);
			double rotatedY = normalY * cos(angle) + normalX * sin(angle);

			double realX = rotatedX + centerX;
			double realY = rotatedY + centerY;

			int scaledX = x_a_coef * realX + x_b_coef;
			int scaledY = y_a_coef * realY + y_b_coef;

			if (scaledX <= img_xlen && scaledX >= 0 && scaledY <= img_ylen && scaledY >= 0) {
				int col = rawData->getRawPixelColour(scaledX, scaledY);
				if (col != 0x000000)
					pSurface->rawSetPixel(iX, iY, col);

			}
		}
	}

	pSurface->mySDLUnlockSurface();
}

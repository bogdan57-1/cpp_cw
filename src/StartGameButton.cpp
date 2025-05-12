#include "header.h"
#include "SpaceInvadersEngine.h"
#include "StartGameButton.h"

void StartGameButton::virtDraw()
{
	drawButton();
	/*std::cout << "Left: " << this->getDrawingRegionLeft() << std::endl <<
		"Top: " << this->getDrawingRegionTop() << std::endl <<
		"Right: " << this->getDrawingRegionRight() << std::endl <<
		"Bottom: " << this->getDrawingRegionBottom() << std::endl;*/
}

void StartGameButton::virtDoUpdate(int iCurrentTime)
{
}

void StartGameButton::drawButton()
{
	int mainColour = 0x868686;
	if (m_pEngine->getCurrentMouseX() >= getDrawingRegionLeft() && m_pEngine->getCurrentMouseX() <= getDrawingRegionRight()
		&& m_pEngine->getCurrentMouseY() >= getDrawingRegionTop() && m_pEngine->getCurrentMouseY() <= getDrawingRegionBottom())
	{
		mainColour = 0xADADA9;
	}
	
	int padding = 5;

	m_pEngine->drawForegroundRectangle(
	this->getDrawingRegionLeft(), this->getDrawingRegionTop(),
		this->getDrawingRegionRight(), this->getDrawingRegionBottom(),
		0x000000);

	m_pEngine->drawForegroundRectangle(
		this->getDrawingRegionLeft() + padding, this->getDrawingRegionTop() + padding,
		this->getDrawingRegionRight() - padding, this->getDrawingRegionBottom() - padding,
		mainColour);

	//just to get the height and the width of the text in pixels...
	//the height is easier (fontSize/2) but width is complicated and i havent figured it out hence this
	SDL_Color color = { (Uint8)((0xffffff & 0xff0000) >> 16), (Uint8)((0xffffff & 0xff00) >> 8), (Uint8)((0xffffff & 0xff)), 0 };
	SDL_Surface* sText = TTF_RenderText_Solid(m_pEngine->getDefaultFont()->getTTFFont(), "Start Game", color);
	

	m_pEngine->drawForegroundString(
		this->getDrawingRegionLeft() + this->getDrawWidth()/2 - sText->w/2,
		this->getDrawingRegionTop() + this->getDrawHeight()/2 - sText->h/2,
		"Start Game", 0xffffff);
}

#include "Button.h"


//Set defaults so that subclasses only override what is necessary

Button::Button(BaseEngine* engine, int width, int height)
	: DisplayableObject(engine, width, height, false)
{
}

void Button::virtDraw()
{
	DisplayableObject::virtDraw();
}

void Button::virtDoUpdate(int iCurrentTime)
{
	DisplayableObject::virtDoUpdate(iCurrentTime);
}

void Button::drawButton()
{

}

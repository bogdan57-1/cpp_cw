#include "header.h"
#include "SpaceInvadersEngine.h"
#include "TextFieldButton.h"

TextFieldButton::TextFieldButton(BaseEngine* engine, int width, int height)
	: Button(engine, width, height)
{
	text = "";
}

void TextFieldButton::virtDraw()
{
	m_pEngine->drawForegroundRectangle(
		getDrawingRegionLeft(), getDrawingRegionTop(), getDrawingRegionRight(), getDrawingRegionBottom(), 0xE1E1E1);
	if (text.size() > 0) {
		m_pEngine->drawForegroundString(
			getDrawingRegionLeft() + 5, getDrawingRegionTop(), text.c_str(), 0x3B3B3B);
	}
}

void TextFieldButton::addCharacter(char a)
{
	if(text.size() < 19) //max size
		text.push_back(a);
}

void TextFieldButton::deleteLastCharacter()
{
	if(text.size() > 0)
		text.pop_back();
}

void TextFieldButton::eraseText()
{
	text.clear();
}

std::string TextFieldButton::getText()
{
	return text;
}

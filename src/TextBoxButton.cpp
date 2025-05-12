#include "header.h"
#include "SpaceInvadersEngine.h"
#include "TextBoxButton.h"

TextBoxButton::TextBoxButton(BaseEngine* engine, int width, int height)
	: Button(engine, width, height)
{
	text = "";
}

void TextBoxButton::virtDraw()
{
	m_pEngine->drawForegroundRectangle(
		getDrawingRegionLeft(), getDrawingRegionTop(), getDrawingRegionRight(), getDrawingRegionBottom(), 0xE1E1E1);
	if (text.size() > 0) {
		std::string temp = "";
		int lineCounter = 0;
		for (int i = 0; i < text.size(); i++) {
			if (text[i] == '\n') {
				//flush text onto screen
				if (temp.size() > 0) {
					m_pEngine->drawForegroundString(
						getDrawingRegionLeft() + 5, getDrawingRegionTop() + lineCounter * 24, temp.c_str(), 0x3B3B3B);
				}
				lineCounter++;
				temp = "";
				continue;
			}

			temp.push_back(text[i]);
		}

	}
}

void TextBoxButton::updateTextFromFile(char* path)
{
	//reinit because im tired of this
	this->m_iDrawHeight = 24;
	text.clear();

	std::ifstream file;
	file.open(path);
	if (file.is_open()) {
		while (!file.eof()) {
			std::string temp = "";
			file >> temp;
			if (temp.size() > 0) { //because an empty file has a line of nothing which can be read
				text.append(temp);
				text.push_back('\n');

				//change the height of the box
				this->m_iDrawHeight += 24; //size of text
			}
			
		}
		file.close();
	}
	else {
		std::cout << "ERROR: could not read from file." << std::endl;
	}
}

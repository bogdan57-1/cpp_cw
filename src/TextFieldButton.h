#pragma once
#include "Button.h"
#include <string>
class TextFieldButton :
    public Button
{
public:
    TextFieldButton(BaseEngine* engine, int width, int height);

    void virtDraw() override;

    void addCharacter(char a);
    void deleteLastCharacter();
    void eraseText();
    std::string getText();

    //To check if we can write to it
    bool isClicked = false;

private:
    std::string text;
};


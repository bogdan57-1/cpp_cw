#pragma once
#include "Button.h"
#include <string>
#include <fstream>
class TextBoxButton :
    public Button
{
public:
    TextBoxButton(BaseEngine* engine, int width, int height);

    void virtDraw() override;

    void updateTextFromFile(char* path);

private:
    std::string text;
};


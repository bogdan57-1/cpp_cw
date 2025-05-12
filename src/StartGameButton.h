#pragma once
#include "Button.h"
class StartGameButton :
    public Button
{
public:
    StartGameButton(BaseEngine* engine, int width, int height)
        : Button(engine, width, height)
    {
    }

    void virtDraw() override;
    void virtDoUpdate(int iCurrentTime) override;
    void drawButton() override;


};


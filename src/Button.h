#pragma once
#include "DisplayableObject.h"
class Button :
    public DisplayableObject
{
public:
    //Buttons will be drawn relative to the centre
    Button(BaseEngine* engine, int width, int height);

    virtual void virtDraw() override;
    virtual void virtDoUpdate(int iCurrentTime) override;
    virtual void drawButton();
    
};


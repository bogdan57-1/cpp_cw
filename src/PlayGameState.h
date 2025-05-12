#pragma once
#include "State.h"
#include "SimpleImage.h"

#define OVERLAY_UPDATE_PERIOD 4

class PlayGameState :
    public State
{
public:
    PlayGameState(SpaceInvadersEngine* engine, StateSystem* stateSystem);

    void setupBackgroundBuffer() override;
    void createSurfaces() override;
    int initialiseObjects() override;
    void mainLoopPreUpdate() override;
    void copyAllBackgroundBuffer() override;
    void keyDown(int iKeyCode) override;
    void mainLoopDoAfterUpdate() override;

private:
    SimpleImage backgroundBase;
    SimpleImage backgroundOverlay;
    int overlayOffset;
    int overlayUpdateCounter;
};


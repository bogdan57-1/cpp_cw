#pragma once
#include "State.h"
#include "DrawingSurface.h"

class PauseState :
    public State
{
public:
    PauseState(SpaceInvadersEngine* engine, StateSystem* stateSystem);
    ~PauseState();

    void setupBackgroundBuffer() override;
    void createSurfaces() override;
    int initialiseObjects() override;
    void keyDown(int iKeyCode) override;
    void mainLoopPreUpdate() override;

private:
    DrawingSurface pauseBackground;
    DrawingSurface* previousBackground;
};


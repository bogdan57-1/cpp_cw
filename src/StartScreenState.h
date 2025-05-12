#pragma once
#include "header.h"
#include "State.h"
#include <vector>

class DrawingSurface;
class SpaceInvadersEngine;
class PixelTileManager;


class StartScreenState :
    public State
{
public:
    StartScreenState(SpaceInvadersEngine* engine, StateSystem* stateSystem);
    ~StartScreenState();

    void renderCurrentBackgroundSurface(double zNoise, int starSize, double starRotation);

    void setupBackgroundBuffer() override;
    void handleMouseDown(int iButton, int iX, int iY) override;
    void mainLoopPreUpdate() override;
    void createSurfaces() override;
    int initialiseObjects() override;
    void mainLoopDoAfterUpdate() override;
    void keyDown(int iKeyCode) override;
    PixelTileManager* getTileManager() override;

private:
    int NUMBER_OF_SURFACES;
    int iCurrentDrawingSurface;
    DrawingSurface* pOriginalSurfaceBackup = nullptr;
    std::vector<DrawingSurface> vecDrawingSurfaces;
    int lastChangedTime = 0;
};


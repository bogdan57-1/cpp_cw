#pragma once
#include "header.h"
#include "BaseEngine.h"
#include <memory>

class StateSystem; 
class PixelTileManager;

class SpaceInvadersEngine :
    public BaseEngine
{
public:
    SpaceInvadersEngine();
    ~SpaceInvadersEngine();
    void virtSetupBackgroundBuffer() override;
    void virtDrawStringsOnTop() override;
    void virtMouseDown(int iButton, int iX, int iY) override;
    int virtInitialise() override;
    void virtMainLoopPreUpdate() override;
    void virtCreateSurfaces() override;
    int virtInitialiseObjects() override;
    void virtMainLoopDoAfterUpdate() override;
    void copyAllBackgroundBuffer() override;
    void virtKeyDown(int iKeyCode) override;

    void setBackgroundSurface(DrawingSurface* newSurface);
    PixelTileManager* getTileManager();


protected:
    std::shared_ptr<StateSystem> m_stateSystem;
};

#pragma once
#include <string>
#include <DisplayInterface/FeatherComponent.h>
#include <Graphics/DirectX9/RenderEngine.h>

#include "FeatherLabel.h"

class FeatherWindowTitle : public FeatherComponent
{
public:
    FeatherLabel* windowTitle;
    DWORD backgroundColor;
    POINT anchorPoint {};
    bool beingDragged;

    FeatherWindowTitle(int posX, int posY, int width, int height, DWORD backgroundColor, ID3DXFont* font, const char* windowTitleText, DWORD color = COLOR(255, 255, 255, 255));
    
    void Render() override;
    void OnMouseDown(FeatherTouch* touch) override;
    void OnMouseUp(FeatherTouch* touch) override;
    void OnLeave(FeatherTouch* touch) override;
};

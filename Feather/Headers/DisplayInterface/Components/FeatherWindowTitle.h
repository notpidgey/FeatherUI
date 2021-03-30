#pragma once
#include <string>
#include <DisplayInterface/FeatherComponent.h>
#include <Graphics/DirectX9/RenderEngine.h>

class FeatherWindowTitle : public FeatherComponent
{
public:
    const char* windowTitleText;
    DWORD backgroundColor;
    POINT anchorPoint {};
    bool beingDragged;

    FeatherWindowTitle(int posX, int posY, int width, int height, DWORD backgroundColor, const char* windowTitleText);
    
    void Render() override;
    void OnMouseDown(FeatherTouch* touch) override;
    void OnMouseUp(FeatherTouch* touch) override;
    void OnLeave(FeatherTouch* touch) override;
};

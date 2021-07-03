#pragma once
#include <memory>
#include <string>
#include <DisplayInterface/Components/FeatherLabel.h>
#include <DisplayInterface/FeatherComponent.h>
#include <Graphics/DirectX9/RenderEngine.h>

class FeatherWindowTitle : public FeatherComponent
{
public:
    FeatherWindowTitle(int posX, int posY, int width, int height, DWORD backgroundColor, ID3DXFont* font, const std::string& windowTitleText, DWORD color = COLOR(255, 255, 255, 255));
private:
    std::shared_ptr<FeatherLabel> windowTitle;
    DWORD backgroundColor;
    POINT anchorPoint {};
    bool beingDragged;
    
    void Render() override;
    void OnMouseDown(FeatherTouch* touch) override;
    void OnMouseUp(FeatherTouch* touch) override;
    void OnLeave(FeatherTouch* touch) override;
};

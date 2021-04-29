#pragma once
#include <functional>
#include <DisplayInterface/FeatherComponent.h>

#include "FeatherLabel.h"

class FeatherButton : public FeatherComponent
{
public:
    std::shared_ptr<FeatherLabel> label;

    FeatherButton(int x, int y, std::function<void(FeatherButton*)>, ID3DXFont* font, std::string& buttonText, DWORD color = COLOR(255, 255, 255, 255));
    FeatherButton(int x, int y, int width, int height, std::function<void(FeatherButton*)>, ID3DXFont* font, std::string& buttonText, DWORD color = COLOR(255, 255, 255, 255));

private:
    std::function<void(FeatherButton*)> onClick;

    DWORD currentFill;
    DWORD fillColor = COLOR(255, 33, 33, 33);
    DWORD fillOnMousePress = COLOR(255, 22, 22, 22);

    DWORD outlineColor = COLOR(255, 22, 22, 22);

    void Render() override;
    void OnMousePressed(FeatherTouch* touch) override;
    void OnMouseUp(FeatherTouch* touch) override;
};

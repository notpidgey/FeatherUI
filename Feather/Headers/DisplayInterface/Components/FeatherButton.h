#pragma once
#include <DisplayInterface/FeatherComponent.h>

#include "FeatherLabel.h"

class FeatherButton : public FeatherComponent
{
public:
    FeatherLabel* label;

    FeatherButton(int x, int y, void (*onClick)(), ID3DXFont* font, const char* buttonText, DWORD color = COLOR(255, 255, 255, 255));
    void Render() override;
    void OnMousePressed(FeatherTouch* touch) override;
    void OnMouseUp(FeatherTouch* touch) override;
private:
    void (*onClick)();
    
    DWORD currentFill;
    DWORD fillColor = COLOR(255, 33, 33, 33);
    DWORD fillOnMousePress = COLOR(255, 22, 22, 22);

    DWORD outlineColor = COLOR(255, 22, 22, 22);
};

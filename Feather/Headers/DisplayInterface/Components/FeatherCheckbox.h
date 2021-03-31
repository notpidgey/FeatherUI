#pragma once
#include <DisplayInterface/Components/FeatherLabel.h>
#include <DisplayInterface/FeatherComponent.h>

class FeatherCheckbox : public FeatherComponent
{
public:
    FeatherLabel* label;
    DWORD currentColor;
    DWORD checkedColor = COLOR(255, 34, 34, 34);
    DWORD uncheckedColor = COLOR(255, 255, 255, 255);
    DWORD outlineColor = COLOR(255, 0, 0, 0);
    bool* value;
    
    FeatherCheckbox(int x, int y, bool* checkValue, ID3DXFont* font, const char* labelText, DWORD color = COLOR(255,0,0,0));
    void Render() override;
    void OnMousePressed(FeatherTouch* touch) override;
    void SetValueFill();
};

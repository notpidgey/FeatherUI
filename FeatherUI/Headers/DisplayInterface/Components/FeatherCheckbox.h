#pragma once
#include <memory>
#include <DisplayInterface/Components/FeatherLabel.h>
#include <DisplayInterface/FeatherComponent.h>

#define CHECKBOX_HEIGHT 20
#define CHECKBOX_WIDTH 20

class FeatherCheckbox : public FeatherComponent
{
public:
    std::shared_ptr<FeatherLabel> label;
    bool* value;
    
    FeatherCheckbox(int x, int y, bool* checkValue, ID3DXFont* font, const std::string& labelText, DWORD color = COLOR(255,0,0,0));
private:
    DWORD currentColor;
    DWORD checkedColor = COLOR(255, 34, 34, 34);
    DWORD uncheckedColor = COLOR(255, 255, 255, 255);
    DWORD outlineColor = COLOR(255, 0, 0, 0);

    void Render() override;
    void OnMousePressed(FeatherTouch* touch) override;
    void SetValueFill();
};

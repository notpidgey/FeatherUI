#pragma once
#include <DisplayInterface/FeatherComponent.h>

#include "FeatherLabel.h"

class FeatherTextBox : public FeatherComponent
{
public:
    FeatherTextBox(int x, int y, int width, int height, ID3DXFont* font, std::string placeHolder);
    
    void Render() override;
    void OnMousePressed(FeatherTouch* touch) override;
    void HandleInput(FeatherTouch* touch) override;

private:
    FeatherLabel* text;
    ID3DXFont* font;
    std::string placeHolder;
    std::string input;
    bool selected;
    bool placeHolderActive = true;
};

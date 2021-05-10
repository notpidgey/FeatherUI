#pragma once
#include <DisplayInterface/FeatherComponent.h>
#include <chrono>
#include <optional>


#include "FeatherLabel.h"

class FeatherTextBox : public FeatherComponent
{
public:
    FeatherTextBox(int x, int y, int width, int height, ID3DXFont* font);
    
    void Render() override;
    void OnMousePressed(FeatherTouch* touch) override;
    void HandleInput(FeatherTouch* touch) override;

private:
    std::shared_ptr<FeatherLabel> text;
    ID3DXFont* font;
    
    int maxCharacters;
    bool selected;
    
    std::optional<std::chrono::system_clock::time_point> firstBackspace;
    std::chrono::system_clock::time_point lastBackspace;
};

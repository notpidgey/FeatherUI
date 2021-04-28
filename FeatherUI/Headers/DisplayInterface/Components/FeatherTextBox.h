#pragma once
#include <DisplayInterface/FeatherComponent.h>
#include <chrono>
#include <optional>


#include "FeatherLabel.h"

class FeatherTextBox : public FeatherComponent
{
public:
    FeatherTextBox(int x, int y, int width, int height, ID3DXFont* font, std::string placeHolder);
    
    void Render() override;
    void OnMousePressed(FeatherTouch* touch) override;
    void HandleInput(FeatherTouch* touch) override;

private:
    std::shared_ptr<FeatherLabel> text;
    ID3DXFont* font;
    
    std::string placeHolder;
    std::string input;
    
    int maxCharacters;
    bool selected;
    bool placeHolderActive = true;
    
    std::optional<std::chrono::system_clock::time_point> firstBackspace;
    std::chrono::system_clock::time_point lastBackspace;
};

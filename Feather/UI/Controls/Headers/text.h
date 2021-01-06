#pragma once
#include <string>

#include "../control.h"

class text : public control
{
public:
    ID3DXFont* font;
    D3DCOLOR color;

    std::string content = "TEST STRING";

    text(float x, float y, ID3DXFont* font, std::string content, D3DCOLOR color = color(255, 255, 255, 255));

    void render() override;
    void handle_mouse() override;
};

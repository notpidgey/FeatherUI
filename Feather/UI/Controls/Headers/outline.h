#pragma once
#include <string>

#include "../control.h"

class outline : public control
{
public:
    D3DCOLOR color = color(255, 255, 0, 0);

    outline(float x, float y, float width, float height, D3DCOLOR color = color(255, 255, 255, 255));
    
    void render() override;
    void handle_mouse() override;
};

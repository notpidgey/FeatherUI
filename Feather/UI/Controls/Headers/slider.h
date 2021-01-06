#pragma once
#include "../control.h"
#include "../../Utils/key_state_manager.h"

class slider : public control
{
public:
    DWORD knob_color = color(255, 255, 255, 255);
    DWORD slider_bar_background = color(255, 34, 34, 34);
    POINT* knob_pos = nullptr;
    float knob_width = 16;
    float knob_height = 16;
    
    float min;
    float max;
    float knob_progression;

    bool being_dragged;

    slider(float x, float y, float min, float max);

    void render() override;
    void handle_mouse() override;
    float get_value();
};

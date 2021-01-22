#pragma once
#include "../control.h"
#include "../../Utils/key_state_manager.h"

#define SLIDER_PADDING 4;

class slider : public control
{
public:
    DWORD knob_color = color(255, 255, 255, 255);
    DWORD slider_bar_background = color(255, 34, 34, 34);
    
    float min;
    float max;

    slider(float x, float y, float min, float max);

    void render() override;
    void render_background() const;
    void render_knob() const;
    void handle_mouse() override;
    float get_value() const;

private:
    POINT* knob_pos_ = nullptr;
    
    const float knob_width_ = 16;
    const float knob_height_ = 16;
    const int knob_padding_ = 2;

    bool being_dragged_;
    float knob_progression_;
};

#include "../Headers/slider.h"

#include <algorithm>
#include <iostream>

slider::slider(float x, float y, float min, float max)
{
    this->x = x;
    this->y = y;
    this->w = 380;
    this->h = 20;
    this->min = min;
    this->max = max;
    this->knob_progression = 0.0;
    this->knob_pos = new POINT();
}

void slider::render()
{
    //Slider background
    draw.rect_filled1(x, y, w, h, slider_bar_background);

    //Slider knob. Add 2 for padding at start add 2 for padding at end. 4 Padding.
    knob_pos->x = x + 2 + (knob_progression * (w-4-knob_width));
    //Align in the middle
    knob_pos->y = y + (h-knob_height)/2;
    draw.rect_filled1(knob_pos->x, knob_pos->y, knob_width, knob_height, knob_color);
}

void slider::handle_mouse()
{
    const auto pixels_per_value = w / max;

    const POINT mouse_point = k_manager->mouse_pos;

    if (k_manager->key_down(VK_LBUTTON))
    {
        if (k_manager->mouse_in_region(knob_pos->x, knob_pos->y, w, h) || being_dragged)
        {
            if (k_manager->key_pressed(VK_LBUTTON) & 1)
            {
                being_dragged = true;
            }

            knob_progression = std::clamp(std::clamp(mouse_point.x-x-4, (float)0, (float)w-knob_width)/(w-2-knob_width), 0.0f, 1.0f);
            std::cout << get_value() << std::endl;
        }       
    }
    else
    {
        being_dragged = false;
    }
}

float slider::get_value()
{
    return min + (knob_progression * (max-min));
}
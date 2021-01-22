#include "../Headers/slider.h"

#include <algorithm>
#include <iostream>

slider::slider(float x, float y, float min, float max): being_dragged_(false)
{
    this->x = x;
    this->y = y;
    this->w = 380;
    this->h = 20;
    this->min = min;
    this->max = max;
    this->knob_progression_ = 0.0;
    this->knob_pos_ = new POINT();
}

void slider::render()
{
    knob_pos_->x = x + knob_padding_ + (knob_progression_ * (w - (knob_padding_ * 2) - knob_width_));
    knob_pos_->y = y + (h - knob_height_) / 2;

    render_background();
    render_knob();
}

void slider::render_background() const
{
    draw.rect_filled1(x, y, w, h, slider_bar_background);
}

void slider::render_knob() const
{
    draw.rect_filled1(knob_pos_->x, knob_pos_->y, knob_width_, knob_height_, knob_color);
}

void slider::handle_mouse()
{
    const POINT mouse_point = k_manager->mouse_pos;

    if (k_manager->key_down(VK_LBUTTON))
    {
        if (k_manager->mouse_in_region(knob_pos_->x, knob_pos_->y, knob_width_, knob_height_) || being_dragged_)
        {
            if (k_manager->key_pressed(VK_LBUTTON) & 1)
            {
                being_dragged_ = true;
            }

            const auto percentage = std::clamp(mouse_point.x - x - 4, static_cast<float>(0), static_cast<float>(w) - knob_width_) / (w - 2 - knob_width_);
            knob_progression_ = std::clamp(percentage, 0.0f, 1.0f);
        }
    }
    else
    {
        being_dragged_ = false;
    }
}

float slider::get_value() const
{
    return min + (knob_progression_ * (max - min));
}
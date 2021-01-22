#include "../Headers/text_box.h"

#include <iostream>

text_box::text_box(float x, float y, float width, float height, ID3DXFont* font)
{
    this->x = x;
    this->y = y;
    this->w = width;
    this->h = height;
    this->font = font;
}

void text_box::render()
{
    draw.rect_filled1(x, y, w, h, background_color);
    draw.rect1(x, y, w, h, background_color);
    draw.string_a(font, x, y, 0, false, color(255, 255, 255, 255), content.c_str());
}

void text_box::handle_mouse()
{
    POINT point = k_manager->mouse_pos;
    
    if (k_manager->key_pressed(VK_LBUTTON))
    {
        if (x + w > point.x && x < point.x && y + h > point.y && y < point.y)
        {
            std::cout << "set to active" << std::endl;
            active = true;
        }
        else
        {
            std::cout << "set non active" << std::endl;
            active = false;
        }
    }
}

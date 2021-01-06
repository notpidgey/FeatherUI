#include "../Headers/text.h"

text::text(float x, float y, ID3DXFont* font, std::string content, D3DCOLOR color)
{
    this->x = x;
    this->y = y;
    this->font = font;
    this->content = content;
    this->color = color;
}

void text::render()
{
    draw.string_a(font, x, y, NULL, false, color, content.c_str());
}

void text::handle_mouse()
{
    //Do Nothing
    //POINT point = k_manager->mouse_pos;
}

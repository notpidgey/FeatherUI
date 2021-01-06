#include "../Headers/outline.h"

outline::outline(float x, float y, float width, float height, D3DCOLOR color)
{
    this->x = x;
    this->y = y;
    this->w = width;
    this->h = height;
    this->color = color;
}

void outline::render()
{
    draw.rect1(x,y,w,h,color);
}

void outline::handle_mouse()
{
    //Do Nothing
    //POINT point = k_manager->mouse_pos;
}

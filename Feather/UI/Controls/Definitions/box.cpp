#include "../Headers/box.h"

box::box(float x, float y, float width, float height, DWORD color, bool filled)
{
	this->x = x;
	this->y = y;
	this->w = width;
	this->h = height;
	this->color = color;
	this->filled = filled;
}

void box::render()
{
	if (filled)
	{
		draw.rect_filled1(x, y, w, h, color);
	}
	else
	{
		draw.rect1(x, y, w, h, color);
	}
}

void box::handle_mouse()
{
	
}
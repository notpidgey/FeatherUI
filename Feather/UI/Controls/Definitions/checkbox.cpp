#include "../Headers/checkbox.h"

checkbox::checkbox(float x, float y, float width, float height, bool* checked)
{
	this->x = x;
	this->y = y;
	this->w = width;
	this->h = height;
	this->checked_ptr = checked;
}

void checkbox::render()
{
	//Draw box outline
	draw.rect1(x, y, w, h, outline_color);
	
	if (*checked_ptr)
	{
		//Draw selected color
		draw.rect_filled1(x + width_padding, y + height_padding, w - (2 * width_padding), h - (2 * height_padding), selected_color);
	}
	else
	{
		//Draw unselected color
		draw.rect_filled1(x + width_padding, y + height_padding, w - (2 * width_padding), h - (2 * height_padding), unselected_color);
	}
}

void checkbox::handle_mouse()
{
	POINT point = k_manager->mouse_pos;
	
	if(k_manager->key_pressed(VK_LBUTTON) & 1)
	{
		if (x + width_padding < point.x && x + w - width_padding > point.x)
		{
			if (y + height_padding < point.y && y + h - height_padding > point.y)
			{
				*checked_ptr = !*checked_ptr;
			}
		}
	}
	else
	{
		//Hover
	}
}
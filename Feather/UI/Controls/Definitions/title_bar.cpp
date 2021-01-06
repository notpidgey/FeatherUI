#include "../Headers/title_bar.h"

title_bar::title_bar(int x, int y, int width, int height, DWORD dword, bool filled, window* window)
{
    this->x = x;
    this->y = y;
    this->w = width;
    this->h = height;
    this->color = color;
    this->filled = filled;
    this->window_parent = window;
}

void title_bar::render()
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

void title_bar::handle_mouse()
{
    const POINT point = k_manager->mouse_pos;

    if (k_manager->key_down(VK_LBUTTON))
    {
        if (k_manager->mouse_in_region(x, y, w, h) || being_dragged)
        {
            if (k_manager->key_pressed(VK_LBUTTON) & 1)
            {
                anchor_pos.x = point.x;
                anchor_pos.y = point.y;
                being_dragged = true;
            }

            window_parent->x += point.x - anchor_pos.x;
            window_parent->y += point.y - anchor_pos.y;

            SetWindowPos(window_parent->hwnd, nullptr, window_parent->x, window_parent->y, window_parent->width,
                         window_parent->height, NULL);
        }
    }
    else
    {
        being_dragged = false;
    }
}

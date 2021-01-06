#pragma once
#include "../control.h"
#include "../../../Window/WINDOW.h"

class title_bar : public control
{
public:
    POINT previous_click;
    DWORD color = color(255, 0, 0, 0);
    window* window_parent;
    POINT anchor_pos;
    bool filled;
    bool being_dragged;

    title_bar(int x, int y, int width, int height, DWORD dword, bool filled,
                  window* hwnd);

    void render() override;
    void handle_mouse() override;
};

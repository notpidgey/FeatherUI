#pragma once
#include <Window/FeatherTouch.h>

bool FeatherTouch::KeyPressed(const int key) noexcept
{
    return keyState[key] == true && prevKeyState[key] == false;
}

bool FeatherTouch::KeyDown(const int key) noexcept
{
    return keyState[key] == true;
}

bool FeatherTouch::KeyReleased(const int key) noexcept
{
    return keyState[key] == false && prevKeyState[key] == true;
}

bool FeatherTouch::MouseInRegion(const int x, const int y, const int w, const int h) const
{
    return mousePos.x >= x && mousePos.y >= y && mousePos.x <= w + x && mousePos.y <= h + y;
}
bool FeatherTouch::MouseInRegion(const POINT& point, const int w, const int h) const
{
    return mousePos.x >= point.x && mousePos.y >= point.y && mousePos.x <= w + point.x && mousePos.y <= h + point.y;
}

void FeatherTouch::PollInput(HWND* hwnd)
{
    for (int i = 0; i < 256; i++)
    {
        prevKeyState[i] = keyState[i];
        keyState[i] = GetAsyncKeyState(i);
    }

    POINT p;
    GetCursorPos(&p);
    ScreenToClient(*hwnd, &p);

    mousePos = {p.x, p.y};
}

#include <iostream>
#include <ostream>
#include <DisplayInterface/Components/FeatherWindowTitle.h>
#include <Window/Window.h>

FeatherWindowTitle::FeatherWindowTitle(const int posX, const int posY, const int width, const int height, const DWORD backgroundColor, const char* windowTitleText)
{
    this->vPosition.x = posX;
    this->vPosition.y = posY;
    this->width = width;
    this->height = height;
    this->backgroundColor = backgroundColor;
    this->windowTitleText = windowTitleText;
    this->beingDragged = false;
}

void FeatherWindowTitle::Render()
{
    g_render.RectFilled(truePosition.x, truePosition.y, width, height, backgroundColor);
}

void FeatherWindowTitle::OnMouseDown(FeatherTouch* touch)
{
    const auto [x, y] = touch->mousePos;

    if (touch->KeyPressed(VK_LBUTTON) & 1)
    {
        anchorPoint.x = x;
        anchorPoint.y = y;
        beingDragged = true;
    }

    touch->window->position.x += x - anchorPoint.x;
    touch->window->position.y += y - anchorPoint.y;

    SetWindowPos(touch->window->hwnd, nullptr, touch->window->position.x, touch->window->position.y, touch->window->width, touch->window->height, NULL);
}

void FeatherWindowTitle::OnMouseUp(FeatherTouch* touch)
{
    beingDragged = false;
}

void FeatherWindowTitle::OnLeave(FeatherTouch* touch)
{
    if (beingDragged)
        OnMouseDown(touch);
    mouseInRegion = true;
}

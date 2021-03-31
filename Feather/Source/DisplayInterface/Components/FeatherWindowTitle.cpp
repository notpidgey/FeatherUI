#include <DisplayInterface/Components/FeatherWindowTitle.h>
#include <Window/Window.h>

#include "DisplayInterface/Components/FeatherLabel.h"

FeatherWindowTitle::FeatherWindowTitle(const int posX, const int posY, const int width, const int height, const DWORD backgroundColor,
    ID3DXFont* font, const char* windowTitleText, const DWORD color)
{
    this->vPosition.x = posX;
    this->vPosition.y = posY;
    this->width = width;
    this->height = height;
    this->backgroundColor = backgroundColor;
    this->beingDragged = false;
    this->windowTitle = new FeatherLabel(10, 6, font, windowTitleText, color);
    this->childrenContainer = new FeatherContainer(this, windowTitle);
}

void FeatherWindowTitle::Render()
{
    g_render.RectFilled(truePosition.x, truePosition.y, width, height, backgroundColor);
    FeatherComponent::Render();
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
    if (beingDragged && GetFocus() == touch->window->hwnd)
        OnMouseDown(touch);
    mouseInRegion = true;
}

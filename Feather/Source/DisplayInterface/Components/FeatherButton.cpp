#include <DisplayInterface/Components/FeatherButton.h>
#include <DisplayInterface/Components/FeatherContainer.h>

FeatherButton::FeatherButton(const int x, const int y, ID3DXFont* font, const char* buttonText, const DWORD color)
{
    const int textWidth = g_render.GetTextWidth(buttonText, font);
    const int textHeight = g_render.GetTextHeight(buttonText, font);

    this->SetPosition(x, y);
    this->width = 150;
    this->height = 25;
    this->label = new FeatherLabel(
        (width / 2) - ( textWidth / 2 ),
        (height / 2) - ( textHeight / 2),
        font, buttonText, color);
    this->childrenContainer = new FeatherContainer(this, label);


    this->currentFill = fillColor;
}

void FeatherButton::Render()
{
    //Main Fill
    g_render.RectFilled1(tPosition.x, tPosition.y, width, height, currentFill);

    //Outline
    g_render.Rect1(tPosition.x, tPosition.y, width, height, outlineColor);

    FeatherComponent::Render();
}

void FeatherButton::OnMousePressed(FeatherTouch* touch)
{
    currentFill = fillOnMousePress;
}

void FeatherButton::OnMouseUp(FeatherTouch* touch)
{
    currentFill = fillColor;
}

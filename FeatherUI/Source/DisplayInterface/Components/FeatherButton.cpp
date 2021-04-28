#include <DisplayInterface/Components/FeatherButton.h>
#include <DisplayInterface/Components/FeatherContainer.h>

FeatherButton::FeatherButton(const int x, const int y, std::function<void(FeatherButton*)> onClick, ID3DXFont* font, const char* buttonText, const DWORD color)
{
    FeatherComponent::SetPosition(x, y);
    this->width = 150;
    this->height = 25;
    this->label = std::make_shared<FeatherLabel>(0,0,font, buttonText, color);
    this->label->vPosition.x = (width / 2) - ( label->GetTextWidth() / 2 );
    this->label->vPosition.y = (height / 2) - ( label->GetTextHeight() / 2);
    this->childrenContainer = std::make_unique<FeatherContainer>(shared, label.get());
    this->onClick = onClick;
    this->currentFill = fillColor;
}

FeatherButton::FeatherButton(const int x, const int y, const int width, const int height, std::function<void(FeatherButton*)> onClick, ID3DXFont* font, const char* buttonText, const DWORD color)
{
    FeatherComponent::SetPosition(x, y);
    this->width = width;
    this->height = height;
    this->label = std::make_shared<FeatherLabel>(0,0,font, buttonText, color);
    this->label->vPosition.x = (width / 2) - ( label->GetTextWidth() / 2 );
    this->label->vPosition.y = (height / 2) - ( label->GetTextHeight() / 2);
    this->childrenContainer = std::make_unique<FeatherContainer>(shared, label.get());
    this->onClick = onClick;
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
    onClick(this);
}

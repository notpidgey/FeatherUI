#include <DisplayInterface/Components/FeatherButton.h>
#include <DisplayInterface/Components/FeatherContainer.h>

FeatherButton::FeatherButton(const int x, const int y, std::function<void(FeatherButton*)> onClick, ID3DXFont* font, const std::string& buttonText, const DWORD color)
{
    FeatherComponent::SetPosition(x, y);
    this->width = 150;
    this->height = 25;
    this->label = std::make_shared<FeatherLabel>(0,0,font, std::string(buttonText), color);
    this->label->SetPosition((width / 2) - ( label->GetTextWidth() / 2 ), (height / 2) - ( label->GetTextHeight() / 2));
    this->childrenContainer = std::make_unique<FeatherContainer>(shared, label.get());
    this->onClick = onClick;
    this->currentFill = fillColor;
}

FeatherButton::FeatherButton(const int x, const int y, const int width, const int height, std::function<void(FeatherButton*)> onClick, ID3DXFont* font, const std::string& buttonText, const DWORD color)
{
    FeatherComponent::SetPosition(x, y);
    this->width = width;
    this->height = height;
    this->label = std::make_shared<FeatherLabel>(0,0,font, std::string(buttonText), color);
    this->label->SetPosition((width / 2) - ( label->GetTextWidth() / 2 ), (height / 2) - ( label->GetTextHeight() / 2));
    this->childrenContainer = std::make_unique<FeatherContainer>(shared, label.get());
    this->onClick = onClick;
    this->currentFill = fillColor;
}

void FeatherButton::SetClickEvent(const std::function<void(FeatherButton*)> function)
{
    this->onClick = function;
}

void FeatherButton::SetFillColor(const D3DCOLOR color)
{
    this->fillColor = color;
}

void FeatherButton::SetMouseClickColor(const D3DCOLOR color)
{
    this->fillOnMousePress = color;
}
void FeatherButton::SetOutlineColor(const D3DCOLOR color)
{
    this->outlineColor = color;
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

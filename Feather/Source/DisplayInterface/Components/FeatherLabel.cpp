#include <DisplayInterface/Components/FeatherLabel.h>
#include <DisplayInterface/Components/FeatherContainer.h>

FeatherLabel::FeatherLabel(const int x, const int y, ID3DXFont* font, std::string* labelText, const DWORD color)
{
    FeatherComponent::SetPosition(x, y);
    this->font = font;
    this->labelText = labelText;
    this->color = color;
    this->width = g_render.GetTextWidth(labelText->data(), font);
    this->height = g_render.GetTextHeight(labelText->data(), font);
}

FeatherLabel::FeatherLabel(const int x, const int y, ID3DXFont* font, const char* labelText, const DWORD color)
{
    this->vPosition.x = x;
    this->vPosition.y = y;
    this->font = font;
    this->labelText = new std::string(labelText);
    this->color = color;
    this->width = g_render.GetTextWidth(labelText, font);
    this->height = g_render.GetTextHeight(labelText, font);
}

void FeatherLabel::Render()
{
    g_render.StringA(font, tPosition.x, tPosition.y, NULL, false, color, labelText->data());
}

int FeatherLabel::GetTextWidth() const
{
    return g_render.GetTextWidth(labelText->data(), font);
}
int FeatherLabel::GetTextHeight() const
{
    return g_render.GetTextHeight(labelText->data(), font);
}

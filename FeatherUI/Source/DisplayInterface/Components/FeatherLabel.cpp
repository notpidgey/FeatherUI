#include <iterator>
#include <FeatherUI/DisplayInterface/Components/FeatherLabel.h>
#include <FeatherUI/DisplayInterface/Components/FeatherContainer.h>

FeatherLabel::FeatherLabel(const int x, const int y, ID3DXFont* font, const std::string& labelText, const DWORD color, const ALIGN_LABEL align)
{
    FeatherComponent::SetPosition(x, y);
    this->labelFont = font;
    this->labelText = std::string(labelText);
    this->color = color;
    this->width = g_render.GetTextWidth(this->labelText, font);
    this->height = g_render.GetTextHeight(this->labelText, font);
    this->labelAlign = align;
}

void FeatherLabel::Render()
{
    switch (labelAlign)
    {
    case LEFT:
        g_render.StringA(labelFont, this, DT_LEFT, false, color, labelText.data());
        break;
    case CENTER:
        g_render.StringA(labelFont, this, DT_CENTER, false, color, labelText.data());
        break;
    case RIGHT:
        g_render.StringA(labelFont, this, DT_RIGHT, false, color, labelText.data());
        break;
    }
}
void FeatherLabel::SetLabelAlign(const ALIGN_LABEL align)
{
    labelAlign = align;
}

void FeatherLabel::SetLabelFont(ID3DXFont* font)
{
    labelFont = font;
}

void FeatherLabel::SetLabelText(const std::string& labelText)
{
    this->labelText = labelText;
}

void FeatherLabel::SetTextHeight(const int height)
{
    this->height = height;
}

void FeatherLabel::SetTextWidth(const int width)
{
    this->width = width;
}

int FeatherLabel::GetTextWidth()
{
    return g_render.GetTextWidth(labelText, labelFont);
}
void FeatherLabel::ResetTextWidth()
{
    this->width = GetTextWidth();
}

int FeatherLabel::GetTextHeight()
{
    return g_render.GetTextHeight(labelText, labelFont);
}

void FeatherLabel::ResetTextHeight()
{
    this->height = GetTextHeight();
}

std::string& FeatherLabel::GetLabelText()
{
    return labelText;
}

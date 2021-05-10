#include <iterator>
#include <DisplayInterface/Components/FeatherLabel.h>
#include <DisplayInterface/Components/FeatherContainer.h>

FeatherLabel::FeatherLabel(const int x, const int y, ID3DXFont* font, const std::string& labelText, const DWORD color, const ALIGN_LABEL align)
{
    FeatherComponent::SetPosition(x, y);
    this->labelFont = font;
    this->labelText = labelText;
    this->color = color;
    this->width = g_render.GetTextWidth(this->labelText, font);
    this->height = g_render.GetTextHeight(this->labelText, font);
    this->labelAlign = align;
}

FeatherLabel::FeatherLabel(const int x, const int y, const int width, const int height, ID3DXFont* font, const std::string& labelText, const DWORD color, const ALIGN_LABEL align)
{
    FeatherComponent::SetPosition(x, y);
    this->labelFont = font;
    this->labelText = labelText;
    this->color = color;
    this->width = width;
    this->height = height;
    this->labelAlign = align;
}

void FeatherLabel::Render()
{
    switch(labelAlign)
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

int FeatherLabel::GetTextWidth()
{
    return g_render.GetTextWidth(labelText, labelFont);
}

int FeatherLabel::GetTextHeight()
{
    return g_render.GetTextHeight(labelText, labelFont);
}

std::string& FeatherLabel::GetLabelText()
{
    return labelText;
}

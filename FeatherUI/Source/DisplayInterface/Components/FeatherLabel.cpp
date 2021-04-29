#include <iterator>
#include <DisplayInterface/Components/FeatherLabel.h>
#include <DisplayInterface/Components/FeatherContainer.h>

/*FeatherLabel::FeatherLabel(const int x, const int y, ID3DXFont* font, std::string* labelText, const DWORD color, const ALIGN_LABEL align)
{
    FeatherComponent::SetPosition(x, y);
    this->font = font;
    this->labelText = labelText;
    this->color = color;
    this->width = g_render.GetTextWidth(labelText->data(), font);
    this->height = g_render.GetTextHeight(labelText->data(), font);
    this->textAlign = align;
}*/

FeatherLabel::FeatherLabel(const int x, const int y, ID3DXFont* font, std::string& labelText, const DWORD color, const ALIGN_LABEL align)
{
    this->vPosition.x = x;
    this->vPosition.y = y;
    this->font = font;
    this->labelText = labelText;
    this->color = color;
    this->width = g_render.GetTextWidth(labelText, font);
    this->height = g_render.GetTextHeight(labelText, font);
    this->textAlign = align;
}

FeatherLabel::FeatherLabel(const int x, const int y, const int width, const int height, ID3DXFont* font, std::string& labelText, const DWORD color, const ALIGN_LABEL align)
{
    FeatherComponent::SetPosition(x, y);
    this->font = font;
    this->labelText = labelText;
    this->color = color;
    this->width = width;
    this->height = height;
    this->textAlign = align;
}

void FeatherLabel::Render()
{
    switch(textAlign)
    {
        case LEFT:
            g_render.StringA(font, this, DT_LEFT, false, color, labelText.data());
            break;
        case CENTER:
            g_render.StringA(font, this, DT_CENTER, false, color, labelText.data());
            break;
        case RIGHT:
            g_render.StringA(font, this, DT_RIGHT, false, color, labelText.data());
            break;
    }
    
}

int FeatherLabel::GetTextWidth()
{
    return g_render.GetTextWidth(labelText, font);
}
int FeatherLabel::GetTextHeight()
{
    return g_render.GetTextHeight(labelText, font);
}

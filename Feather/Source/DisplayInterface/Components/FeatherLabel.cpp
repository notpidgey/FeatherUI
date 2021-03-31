#include <DisplayInterface/Components/FeatherLabel.h>

FeatherLabel::FeatherLabel(const int x, const int y, ID3DXFont* font, const char* labelText, const DWORD color)
{
    this->vPosition.x = x;
    this->vPosition.y = y;
    this->font = font;
    this->labelText = labelText;
    this->color = color;
}

void FeatherLabel::Render()
{
    g_render.StringA(font, truePosition.x, truePosition.y, NULL, false, color, labelText);
}

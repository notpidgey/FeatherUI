#include <DisplayInterface/Components/FeatherCheckbox.h>
#include <DisplayInterface/Components/FeatherContainer.h>

FeatherCheckbox::FeatherCheckbox(const int x, const int y, bool* checkValue, ID3DXFont* font, const char* labelText, const DWORD color)
{
    SetPosition(x,y);
    this->width = 20,
    this->height = 20;
    this->value = checkValue;
    this->label = new FeatherLabel(30, 2, font, labelText, color);
    this->childrenContainer = new FeatherContainer(this, label);
    SetValueFill();
}

void FeatherCheckbox::Render()
{
    //Render outline
    g_render.Rect1(tPosition.x, tPosition.y, width, height, outlineColor);
    
    // Render Inside
    g_render.RectFilled1(tPosition.x + 2, tPosition.y + 2, width - 4, height - 4, currentColor);

    FeatherComponent::Render();
}

void FeatherCheckbox::OnMousePressed(FeatherTouch* touch)
{
    *value = !*value;
    SetValueFill();
}

void FeatherCheckbox::SetValueFill()
{
    if(*value)
        currentColor = checkedColor;
    else
        currentColor = uncheckedColor;
}

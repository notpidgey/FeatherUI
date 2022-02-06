#include <FeatherUI/DisplayInterface/Components/FeatherCheckbox.h>
#include <FeatherUI/DisplayInterface/Components/FeatherContainer.h>

FeatherCheckbox::FeatherCheckbox(const int x, const int y, std::atomic<bool>* checkValue, ID3DXFont* font, const std::string& labelText, const DWORD color)
{
    FeatherComponent::SetPosition(x, y);
    this->value = checkValue;
    this->label = std::make_shared<FeatherLabel>(25, 2, font, labelText, color);
    this->childrenContainer = std::make_unique<FeatherContainer>(shared, label.get());
    this->width = CHECKBOX_WIDTH + 15 + label->GetTextWidth(),
    this->height = CHECKBOX_HEIGHT;

    SetValueFill();
}

void FeatherCheckbox::Render()
{
    //Render outline
    g_render.Rect1(tPosition.x, tPosition.y, CHECKBOX_WIDTH, CHECKBOX_HEIGHT, outlineColor);

    // Render Inside
    g_render.RectFilled1(tPosition.x + 2, tPosition.y + 2, CHECKBOX_WIDTH - 4, CHECKBOX_HEIGHT - 4, currentColor);

    FeatherComponent::Render();
}

void FeatherCheckbox::OnMousePressed(FeatherTouch* touch)
{
    *value = !value->load();
    SetValueFill();
}

void FeatherCheckbox::SetValueFill()
{
    if (value->load())
        currentColor = checkedColor;
    else
        currentColor = uncheckedColor;
}

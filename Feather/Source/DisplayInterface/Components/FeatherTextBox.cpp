#include <DisplayInterface/Components/FeatherTextBox.h>
#include <DisplayInterface/Components/FeatherContainer.h>
#include <algorithm>

FeatherTextBox::FeatherTextBox(const int x, const int y, const int width, const int height, ID3DXFont* font, const std::string placeHolder)
{
    this->FeatherComponent::SetPosition(x, y);
    this->width = width;
    this->height = height;
    this->font = font;
    this->text = new FeatherLabel(2, 2, font, &input, COLOR(255, 255, 255, 255));
    this->text->width = width - 4;
    this->text->height = height - 4;
    this->input = placeHolder;
    this->childrenContainer = new FeatherContainer(this, text);
}

void FeatherTextBox::Render()
{
    g_render.RectFilled1(tPosition.x, tPosition.y, width, height, COLOR(255, 33, 33, 33));

    if(selected)
    {
        const int cursorOffset = std::clamp(text->GetTextWidth(), 0, width);
        g_render.RectFilled1(tPosition.x + cursorOffset, tPosition.y + 2, 2, height-4, COLOR(255,255,255,255));
    }

    FeatherComponent::Render();
}

void FeatherTextBox::OnMousePressed(FeatherTouch* touch)
{
    selected = !selected;

    if (placeHolderActive)
    {
        if (selected)
        {
            placeHolderActive = false;
            input = "";
        }
    }
    else if (input.length() == 0)
    {
        if (!selected)
        {
            input = placeHolder;
        }
    }
}

void FeatherTextBox::HandleInput(FeatherTouch* touch)
{
    if (selected)
    {
        if (touch->KeyPressed(0x20))
            input += ' ';
        if (touch->KeyDown(0x08) && input.size() > 0)
            input.pop_back();
        else
            for (int i = 0x41; i <= 0x5A; i ++)
            {
                if (touch->KeyPressed(i))
                {
                    const char character = static_cast<char>(MapVirtualKeyA(i, MAPVK_VK_TO_CHAR));
                    if (touch->KeyDown(0x10))
                        input += character;
                    else input += tolower(character);
                }
            }
    }

    FeatherComponent::HandleInput(touch);
}

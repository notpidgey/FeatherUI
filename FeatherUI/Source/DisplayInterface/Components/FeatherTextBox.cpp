#include <DisplayInterface/Components/FeatherTextBox.h>
#include <DisplayInterface/Components/FeatherContainer.h>
#include <algorithm>
#include <iostream>

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
    this->lastBackspace = std::chrono::system_clock::now();
    this->maxCharacters = 0;
}

void FeatherTextBox::Render()
{
    g_render.RectFilled1(tPosition.x, tPosition.y, width, height, COLOR(255, 33, 33, 33));

    if(selected)
    {
        const int cursorOffset = std::clamp(text->GetTextWidth(), 0, width) + 2;
        g_render.RectFilled1(tPosition.x + cursorOffset, tPosition.y + 3, 2, height-6, COLOR(255,255,255,255));
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
        if(touch->KeyReleased(0x08))
        {
            firstBackspace = std::nullopt;
        }
        else if(touch->KeyPressed(0x08) && input.size() > 0)
        {
            firstBackspace = std::chrono::system_clock::now();
            input.pop_back();
        }
        else if (touch->KeyDown(0x08) && input.size() > 0 &&
            (std::chrono::system_clock::now() - firstBackspace.value()).count() >= 3000000  &&
            (std::chrono::system_clock::now() - lastBackspace).count() >= 150000)
        {
            lastBackspace = std::chrono::system_clock::now();
            input.pop_back();
        }

        if(maxCharacters != 0 && input.size() >= maxCharacters)
            return;
        
        if (touch->KeyPressed(0x20))
            input += ' ';
        else
        {
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
    }

   
    FeatherComponent::HandleInput(touch);
}

#include <FeatherUI/DisplayInterface/Components/FeatherTextBox.h>
#include <FeatherUI/DisplayInterface/Components/FeatherContainer.h>
#include <algorithm>
#include <iostream>

FeatherTextBox::FeatherTextBox(const int x, const int y, const int width, const int height, ID3DXFont* font)
{
    this->FeatherComponent::SetPosition(x, y);
    this->width = width;
    this->height = height;
    this->font = font;
    this->text = std::make_shared<FeatherLabel>(2, 2, font, "", COLOR(255, 255, 255, 255));
    this->text->SetWidth(width - 4);
    this->text->SetHeight(height - 4);
    this->childrenContainer = std::make_unique<FeatherContainer>(shared, text.get());
    this->lastBackspace = std::chrono::system_clock::now();
    this->maxCharacters = 0;
    this->selected = false;
}

void FeatherTextBox::Render()
{
    g_render.RectFilled1(tPosition.x, tPosition.y, width, height, COLOR(255, 33, 33, 33));

    if (selected)
    {
        const int cursorOffset = std::clamp(text->GetTextWidth(), 0, width) + 2;
        g_render.RectFilled1(tPosition.x + cursorOffset, tPosition.y + 3, 2, height - 6, COLOR(255, 255, 255, 255));
    }

    FeatherComponent::Render();
}

void FeatherTextBox::OnMousePressed(FeatherTouch* touch)
{
    selected = !selected;
}

void FeatherTextBox::OnMouseClickAway(FeatherTouch* touch)
{
    selected = false;
}

void FeatherTextBox::HandleInput(FeatherTouch* touch)
{
    if (selected)
    {
        if (touch->KeyReleased(0x08))
        {
            firstBackspace = std::nullopt;
        }
        else if (touch->KeyPressed(0x08) && text->GetLabelText().size() > 0)
        {
            firstBackspace = std::chrono::system_clock::now();
            text->GetLabelText().pop_back();
        }
        else if (touch->KeyDown(0x08) && text->GetLabelText().size() > 0 &&
                 (std::chrono::system_clock::now() - firstBackspace.value()).count() >= 3000000 &&
                 (std::chrono::system_clock::now() - lastBackspace).count() >= 150000)
        {
            lastBackspace = std::chrono::system_clock::now();
            text->GetLabelText().pop_back();
        }

        if (touch->KeyPressed(VK_RETURN))
        {
            selected = false;
            return;
        }

        if (maxCharacters != 0 && text->GetLabelText().size() >= maxCharacters)
            return;
        if(touch->KeyPressed(0x11))
            return;

        if (touch->KeyPressed(0x20))
            text->GetLabelText() += ' ';
        else if (!touch->KeyPressed(VK_CONTROL))
        {
            for (int i = 0x30; i <= 0x5A; i ++)
            {
                if (touch->KeyPressed(i))
                {
                    if (const char character = static_cast<char>(MapVirtualKeyA(i, MAPVK_VK_TO_CHAR)); touch->KeyDown(0x10))
                    {
                        if (std::isdigit(character))
                        {
                            switch (character - 48)
                            {
                            case 1:
                                text->GetLabelText() += "!";
                                break;
                            case 2:
                                text->GetLabelText() += "@";
                                break;
                            case 3:
                                text->GetLabelText() += "#";
                                break;
                            case 4:
                                text->GetLabelText() += "$";
                                break;
                            case 5:
                                text->GetLabelText() += "%";
                                break;
                            case 6:
                                text->GetLabelText() += "^";
                                break;
                            case 7:
                                text->GetLabelText() += "&";
                                break;
                            case 8:
                                text->GetLabelText() += "*";
                                break;
                            case 9:
                                text->GetLabelText() += "(";
                                break;
                            case 0:
                                text->GetLabelText() += ")";
                                break;
                            default:
                                break;
                            }
                        }
                        else
                        {
                            text->GetLabelText() += character;
                        }
                    }

                    else text->GetLabelText() += tolower(character);
                }
            }
        }
    }


    FeatherComponent::HandleInput(touch);
}
std::string* FeatherTextBox::GetText() const
{
    return &text->GetLabelText();
}

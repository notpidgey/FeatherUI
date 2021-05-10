#pragma once
#include <DisplayInterface/FeatherComponent.h>
#include <Graphics/DirectX9/Structs/FeatherFont.h>

class FeatherLabel : public FeatherComponent
{
public:
    enum ALIGN_LABEL
    {
        LEFT,
        CENTER,
        RIGHT
    };
    
    FeatherLabel(int x, int y,                        ID3DXFont* font, const std::string& labelText, DWORD color = COLOR(255, 255, 255, 255), ALIGN_LABEL align = LEFT);
    FeatherLabel(int x, int y, int width, int height, ID3DXFont* font, const std::string& labelText, DWORD color = COLOR(255, 255, 255, 255), ALIGN_LABEL align = LEFT);

    int GetTextWidth();
    int GetTextHeight();
    std::string& GetLabelText();
    
    void Render() override;
    void SetLabelAlign(ALIGN_LABEL align);
    void SetLabelFont(ID3DXFont* font);
    void SetLabelText(const std::string& labelText);

protected:
    D3DCOLOR color;
    
    ALIGN_LABEL labelAlign;
    ID3DXFont* labelFont;
    std::string labelText;
};

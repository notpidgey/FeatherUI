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
    
    ID3DXFont* font;
    std::string* labelText;
    
    FeatherLabel(int x, int y, ID3DXFont* font, std::string* labelText, DWORD color = COLOR(255, 255, 255, 255), ALIGN_LABEL align = LEFT);
    FeatherLabel(int x, int y, ID3DXFont* font, const char* labelText, DWORD color = COLOR(255, 255, 255, 255), ALIGN_LABEL align = LEFT);
    FeatherLabel(int x, int y, int width, int height, ID3DXFont* font, const char* labelText, DWORD color, ALIGN_LABEL align);
    
    int GetTextWidth() const;
    int GetTextHeight() const;
    
    void Render() override;

private:
    ALIGN_LABEL textAlign;
    DWORD color;
};

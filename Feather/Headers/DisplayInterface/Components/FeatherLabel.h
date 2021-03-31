#pragma once
#include <DisplayInterface/FeatherComponent.h>
#include <Graphics/DirectX9/Structs/FeatherFont.h>

class FeatherLabel : public FeatherComponent
{
public:
    ID3DXFont* font;
    DWORD color;
    const char* labelText;
    
    FeatherLabel(int x, int y, ID3DXFont* font, const char* labelText, DWORD color = COLOR(255, 255, 255, 255));
    void Render() override;
};

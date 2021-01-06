#pragma once
#include <d3dx9core.h>
#include <string>

struct font
{
    font()
    {
        
    }
    
    font(ID3DXFont** d3d_font, std::string name, int font_size)
    {
        this->d3d_font = d3d_font;
        this->name = name;
        this->font_size = font_size;
    }

    ID3DXFont** d3d_font;
    std::string name;
    int font_size;
};

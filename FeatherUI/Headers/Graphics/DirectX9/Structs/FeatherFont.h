#pragma once
#include <d3dx9core.h>
#include <string>

struct FeatherFont
{
    FeatherFont(): d3dFont(nullptr), fontSize(0)
    {
        //Default Constructor
    }

    FeatherFont(ID3DXFont** d3dFont, const std::string name, const int fontSize)
    {
        this->d3dFont = d3dFont;
        this->name = name;
        this->fontSize = fontSize;
    }

    ID3DXFont** d3dFont;
    std::string name;
    int fontSize;
};

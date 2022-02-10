#pragma once
#include <d3dx9core.h>
#include <string>

struct FeatherFont
{
    ID3DXFont** d3dFont;
    std::string name;
    int fontSize;
	int charSet;
};

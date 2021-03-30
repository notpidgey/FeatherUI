#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include <vector>

#define COLOR(a,r,g,b) D3DCOLOR_ARGB(a,r,g,b)
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

class RenderEngine
{
public:
    LPDIRECT3DDEVICE9 pDevice = nullptr;
    ID3DXLine* pLine = nullptr;
    
    struct Vertex
    {
        float x, y, z = 0, rhw = 1;
        DWORD color = 0;
    };
    
    void SetPointers(LPDIRECT3DDEVICE9 pDev, ID3DXLine* pLin);
    void Line(float x, float y, float x1, float y1, bool aa, DWORD color, float width = 1.f) const;
    void StringA(ID3DXFont* font, float x, float y, DWORD flags, bool shadow, DWORD color, const char* string, ...);
    void StringW(ID3DXFont* font, float x, float y, DWORD flags, bool shadow, DWORD color, const wchar_t* string, ...) const;
    void Rect1(float x, float y, float w, float h, DWORD color) const;
    void Rect(float x, float y, float x1, float y1, DWORD color) const;
    void RectFilled(float x, float y, float x1, float y1, DWORD color) const;
    void RectFilled1(float x, float y, float w, float h, DWORD color) const;
    void Circle(float x, float y, float size, int resolution, DWORD color) const;
    void CircleFilled(float x, float y, float size, int resolution, DWORD color) const;
};

extern RenderEngine g_render;
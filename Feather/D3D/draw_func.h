#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include <vector>

#define color(a,r,g,b) D3DCOLOR_ARGB(a,r,g,b)
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

class draw_func
{
public:
	LPDIRECT3DDEVICE9 pDevice = nullptr;
	ID3DXLine* pLine = nullptr;

	struct vertex
	{
		float x, y, z = 0, rhw = 1;
		DWORD color = 0;
	};

	void set_pointers(LPDIRECT3DDEVICE9 pDev, ID3DXLine* pLin);
	void line(float x, float y, float x1, float y1, bool aa, DWORD color, float width = 1.f);
	void string_a(ID3DXFont* font, float x, float y, DWORD flags, bool shadow, DWORD color, const char* string, ...);
	void string_w(ID3DXFont* font, float x, float y, DWORD flags, bool shadow, DWORD color, const wchar_t* string, ...);
	void rect1(float x, float y, float w, float h, DWORD color);
	void rect(float x, float y, float x1, float y1, DWORD color);
	void rect_filled(float x, float y, float x1, float y1, DWORD color);
	void rect_filled1(float x, float y, float w, float h, DWORD color);
	void circle(float x, float y, float size, int resolution, DWORD color);
	void circle_filled(float x, float y, float size, int resolution, DWORD color);
};

extern draw_func draw;
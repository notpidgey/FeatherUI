#pragma once
#include <d3dx9.h>
#include <d3d9.h>

#include <vector>

#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

class fonts
{
public:
	ID3DXFont* montserrat24px = nullptr;
};

#define color(a,r,g,b) D3DCOLOR_ARGB(a,r,g,b)

class draw_func
{
public:
	LPDIRECT3DDEVICE9 pDevice = nullptr;
	ID3DXLine* pLine = nullptr;

	void set_pointers(LPDIRECT3DDEVICE9 pDev, ID3DXLine* pLin);

	struct vertex
	{
		float x, y, z = 0, rhw = 1;
		DWORD color = 0;
	};

	void line(float x, float y, float x1, float y1, bool aa, DWORD color, float width = 1.f);

	//DT_LEFT - DT_CENTER - DT_RIGHT
	void string_a(ID3DXFont* font, float x, float y, DWORD flags, bool shadow, DWORD color, const char* string, ...);

	//DT_LEFT - DT_CENTER - DT_RIGHT
	void string_w(ID3DXFont* font, float x, float y, DWORD flags, bool shadow, DWORD color, const wchar_t* string, ...);

	void rect1(float x, float y, float w, float h, DWORD color);

	void rect(float x, float y, float x1, float y1, DWORD color);

	void rect_filled(float x, float y, float x1, float y1, DWORD color);

	void rect_filled1(float x, float y, float w, float h, DWORD color);

	void circle(float x, float y, float size, int resolution, DWORD color);

	void circle_filled(float x, float y, float size, int resolution, DWORD color);
};

extern draw_func draw;
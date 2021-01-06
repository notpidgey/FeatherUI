#include "draw_func.h"

void draw_func::set_pointers(LPDIRECT3DDEVICE9 pDev, ID3DXLine* pLin)
{
	draw_func::pDevice = pDev;
	draw_func::pLine = pLine;
}

void draw_func::line(float x, float y, float x1, float y1, bool aa, DWORD color, float width)
{
	D3DXVECTOR2 vertices[] = { {x,y},{x1,y1} };
	pLine->SetWidth(width);
	pLine->SetAntialias(aa);
	pLine->Begin();
	pLine->Draw(vertices, 2, color);
	pLine->End();
}

void draw_func::string_a(ID3DXFont* font, float x, float y, DWORD flags, bool shadow, DWORD color, const char* string, ...)
{
	RECT r = { x,y,x,y };

	static char buf[200] = { 0 };

	va_list arg_list;
	va_start(arg_list, string);
	vsnprintf(buf, sizeof(buf), string, arg_list);
	va_end(arg_list);

	if (shadow)
	{
		RECT r1 = { x + 2,y,x,y };
		font->DrawTextA(NULL, buf, -1, &r1, flags | DT_NOCLIP, 0xFF636363);
	}

	font->DrawTextA(NULL, buf, -1, &r, flags | DT_NOCLIP, color);
}

void draw_func::string_w(ID3DXFont* font, float x, float y, DWORD flags, bool shadow, DWORD color, const wchar_t* string, ...)
{
	RECT r = { x,y,x,y };

	static wchar_t b[200] = { 0 };

	va_list args;
	va_start(args, string);
	vswprintf(b, 200, string, args);
	va_end(args);


	if (shadow)
	{
		RECT r1 = { x + 2,y,x,y };
		font->DrawTextW(NULL, b, -1, &r1, flags | DT_NOCLIP, 0xFF636363);
	}

	font->DrawTextW(NULL, b, -1, &r, flags | DT_NOCLIP, color);
}

void draw_func::rect1(float x, float y, float w, float h, DWORD color)
{
	w -= 1;
	h -= 1;
	draw_func::vertex vertices[] = {
			{x,y,0.5,1,color},
			{x + w,y,0.5,1,color},
			{x + w,y + h,0.5,1,color},
			{x,y + h,0.5,1,color},
			{x,y,0.5,1,color}
	};


	LPDIRECT3DVERTEXBUFFER9 v_buffer;
	if (FAILED(pDevice->CreateVertexBuffer(5 * sizeof(draw_func::vertex), 0, D3DFVF_XYZRHW | D3DFVF_DIFFUSE, D3DPOOL_DEFAULT, &v_buffer, NULL)))
	{
		return;
	}

	void* pvoid;
	v_buffer->Lock(0, 0, &pvoid, 0);
	memcpy(pvoid, vertices, sizeof(vertices));
	v_buffer->Unlock();

	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	pDevice->SetStreamSource(0, v_buffer, 0, sizeof(draw_func::vertex));
	pDevice->DrawPrimitive(D3DPT_LINESTRIP, 0, 4);
	v_buffer->Release();
}

void draw_func::rect(float x, float y, float x1, float y1, DWORD color)
{
	draw_func::vertex vertices[] = {
		{x,y,0.5,1,color},
		{x1,y,0.5,1,color},
		{x1,y1,0.5,1,color},
		{x,y1,0.5,1,color},
		{x,y,0.5,1,color}
	};

	LPDIRECT3DVERTEXBUFFER9 v_buffer = NULL;
	if (FAILED(pDevice->CreateVertexBuffer(5 * sizeof(draw_func::vertex), 0, D3DFVF_XYZRHW | D3DFVF_DIFFUSE, D3DPOOL_DEFAULT, &v_buffer, NULL)))
	{
		return;
	}

	void* pvoid;
	v_buffer->Lock(0, 0, &pvoid, 0);
	memcpy(pvoid, vertices, sizeof(vertices));
	v_buffer->Unlock();

	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	pDevice->SetStreamSource(0, v_buffer, 0, sizeof(draw_func::vertex));
	pDevice->DrawPrimitive(D3DPT_LINESTRIP, 0, 4);
	v_buffer->Release();
}

void draw_func::rect_filled(float x, float y, float x1, float y1, DWORD color)
{
	draw_func::vertex vertices[] = {
		{x,y1,0.5,1,color},
		{x,y,0.5,1,color},
		{x1,y1,0.5,1,color},
		{x1,y,0.5,1,color}
	};

	LPDIRECT3DVERTEXBUFFER9 v_buffer = NULL;
	if (FAILED(pDevice->CreateVertexBuffer(6 * sizeof(draw_func::vertex), 0, D3DFVF_XYZRHW | D3DFVF_DIFFUSE, D3DPOOL_DEFAULT, &v_buffer, NULL)))
	{
		return;
	}

	void* pvoid;
	v_buffer->Lock(0, 0, &pvoid, 0);
	memcpy(pvoid, vertices, sizeof(vertices));
	v_buffer->Unlock();

	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	pDevice->SetStreamSource(0, v_buffer, 0, sizeof(draw_func::vertex));
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	v_buffer->Release();
}

void draw_func::rect_filled1(float x, float y, float w, float h, DWORD color)
{
	draw_func::vertex vertices[] = {
		{x,y + h,0.5,1,color},
		{x,y,0.5,1,color},
		{x + w,y + h,0.5,1,color},
		{x + w,y,0.5,1,color}
	};

	LPDIRECT3DVERTEXBUFFER9 v_buffer = NULL;
	if (FAILED(pDevice->CreateVertexBuffer(6 * sizeof(draw_func::vertex), 0, D3DFVF_XYZRHW | D3DFVF_DIFFUSE, D3DPOOL_DEFAULT, &v_buffer, NULL)))
	{
		return;
	}

	void* pvoid;
	v_buffer->Lock(0, 0, &pvoid, 0);
	memcpy(pvoid, vertices, sizeof(vertices));
	v_buffer->Unlock();

	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	pDevice->SetStreamSource(0, v_buffer, 0, sizeof(draw_func::vertex));
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	v_buffer->Release();
}

void draw_func::circle(float x, float y, float size, int resolution, DWORD color)
{
	std::vector<draw_func::vertex> vertices(resolution + 2);

	for (int i = 0; i < resolution + 2; ++i)
	{
		vertices[i].x = x - size * cos(i * (2 * D3DX_PI / resolution));
		vertices[i].y = y - size * sin(i * (2 * D3DX_PI / resolution));
		vertices[i].color = color;
		vertices[i].z = 0.5;
		vertices[i].rhw = 1;
	}

	LPDIRECT3DVERTEXBUFFER9 v_buffer = NULL;
	if (FAILED(pDevice->CreateVertexBuffer((resolution + 2) * sizeof(draw_func::vertex), 0, D3DFVF_XYZRHW | D3DFVF_DIFFUSE, D3DPOOL_DEFAULT, &v_buffer, NULL)))
	{
		return;
	}

	void* pvoid;
	v_buffer->Lock(0, 0, &pvoid, 0);
	memcpy(pvoid, &vertices[0], (resolution + 2) * sizeof(draw_func::vertex));
	v_buffer->Unlock();

	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	pDevice->SetStreamSource(0, v_buffer, 0, sizeof(draw_func::vertex));
	pDevice->DrawPrimitive(D3DPT_LINESTRIP, 0, resolution);
	v_buffer->Release();
}

void draw_func::circle_filled(float x, float y, float size, int resolution, DWORD color)
{
	std::vector<draw_func::vertex> vertices(resolution + 2);

	for (int i = 0; i < resolution + 2; ++i)
	{
		vertices[i].x = x - size * cos(i * (2 * D3DX_PI / resolution));
		vertices[i].y = y - size * sin(i * (2 * D3DX_PI / resolution));
		vertices[i].color = color;
		vertices[i].z = 0.5;
		vertices[i].rhw = 1;
	}

	LPDIRECT3DVERTEXBUFFER9 v_buffer = NULL;
	if (FAILED(pDevice->CreateVertexBuffer((resolution + 2) * sizeof(draw_func::vertex), 0, D3DFVF_XYZRHW | D3DFVF_DIFFUSE, D3DPOOL_DEFAULT, &v_buffer, NULL)))
	{
		return;
	}

	void* pvoid;
	v_buffer->Lock(0, 0, &pvoid, 0);
	memcpy(pvoid, &vertices[0], (resolution + 2) * sizeof(draw_func::vertex));
	v_buffer->Unlock();

	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	pDevice->SetStreamSource(0, v_buffer, 0, sizeof(draw_func::vertex));
	pDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, resolution);
	v_buffer->Release();
}

draw_func draw;
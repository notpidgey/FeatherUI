#include <ostream>
#include <vector>
#include <string>
#include <FeatherUI/Graphics/DirectX9/RenderEngine.h>
#include <FeatherUI/DisplayInterface/FeatherComponent.h>

void RenderEngine::SetPointers(const LPDIRECT3DDEVICE9 pDev, ID3DXLine* pLin)
{
	pDevice = pDev;
	pLine = pLin;
}

void RenderEngine::Line(const float x, const float y, const float x1, const float y1, const bool aa, const DWORD color,
	const float width) const
{
	D3DXVECTOR2 vertices[] = {{ x,  y },
							  { x1, y1 }};
	pLine->SetWidth(width);
	pLine->SetAntialias(aa);
	pLine->Begin();
	pLine->Draw(vertices, 2, color);
	pLine->End();
}

void RenderEngine::StringA(ID3DXFont* font, FeatherComponent* component, const DWORD flags, const bool shadow,
	const DWORD color, const char* string)
{
	RECT r = { component->GetTrueX(), component->GetTrueY(), component->GetTrueX() + component->GetWidth(),
		component->GetTrueY() + component->GetHeight() };
	if (shadow)
	{
		RECT r1 = { r.left + 2, r.top, r.right, r.bottom };
		font->DrawTextA(nullptr, string, -1, &r1, flags, 0xFF636363);
	}

	font->DrawTextA(nullptr, string, -1, &r, flags, color);
}


void RenderEngine::StringA(ID3DXFont* font, const float x, const float y, const DWORD flags, const bool shadow,
	const DWORD color, const char* string)
{
	RECT r = { x, y, x, y };
	if (shadow)
	{
		RECT r1 = { x + 2, y, x, y };
		font->DrawTextA(nullptr, string, -1, &r1, flags | DT_NOCLIP, 0xFF636363);
	}

	font->DrawTextA(nullptr, string, -1, &r, flags | DT_NOCLIP, color);
}

void RenderEngine::StringW(ID3DXFont* font, FeatherComponent* component, const DWORD flags, const bool shadow,
	const DWORD color, const wchar_t* string)
{
	RECT r = { component->GetTrueX(), component->GetTrueY(), component->GetTrueX() + component->GetWidth(),
		component->GetTrueY() + component->GetHeight() };
	if (shadow)
	{
		RECT r1 = { r.left + 2, r.top, r.right, r.bottom };
		font->DrawTextW(nullptr, string, -1, &r1, flags, 0xFF636363);
	}

	font->DrawTextW(nullptr, string, -1, &r, flags, color);
}

void RenderEngine::StringW(ID3DXFont* font, const float x, const float y, const DWORD flags, const bool shadow,
	const DWORD color, const wchar_t* string) const
{
	RECT r = { x, y, x, y };
	if (shadow)
	{
		RECT r1 = { x + 2, y, x, y };
		font->DrawTextW(nullptr, string, -1, &r1, flags | DT_NOCLIP, 0xFF636363);
	}

	font->DrawTextW(nullptr, string, -1, &r, flags | DT_NOCLIP, color);
}

void RenderEngine::Rect1(const float x, const float y, float w, float h, const DWORD color) const
{
	w -= 1;
	h -= 1;
	Vertex vertices[] = {
		{ x,     y,     0.5, 1, color },
		{ x + w, y,     0.5, 1, color },
		{ x + w, y + h, 0.5, 1, color },
		{ x,     y + h, 0.5, 1, color },
		{ x,     y,     0.5, 1, color }
	};


	LPDIRECT3DVERTEXBUFFER9 vBuffer;
	if (FAILED(pDevice->CreateVertexBuffer(5 * sizeof(RenderEngine::Vertex), 0, D3DFVF_XYZRHW | D3DFVF_DIFFUSE,
		D3DPOOL_DEFAULT, &vBuffer, NULL)))
	{
		return;
	}

	void* pVoid;
	vBuffer->Lock(0, 0, &pVoid, 0);
	memcpy(pVoid, vertices, sizeof(vertices));
	vBuffer->Unlock();

	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	pDevice->SetStreamSource(0, vBuffer, 0, sizeof(Vertex));
	pDevice->DrawPrimitive(D3DPT_LINESTRIP, 0, 4);
	vBuffer->Release();
}

void RenderEngine::Rect(const float x, const float y, const float x1, const float y1, const DWORD color) const
{
	Vertex vertices[] = {
		{ x,  y,  0.5, 1, color },
		{ x1, y,  0.5, 1, color },
		{ x1, y1, 0.5, 1, color },
		{ x,  y1, 0.5, 1, color },
		{ x,  y,  0.5, 1, color }
	};

	LPDIRECT3DVERTEXBUFFER9 vBuffer = nullptr;
	if (FAILED(pDevice->CreateVertexBuffer(5 * sizeof(RenderEngine::Vertex), 0, D3DFVF_XYZRHW | D3DFVF_DIFFUSE,
		D3DPOOL_DEFAULT, &vBuffer, NULL)))
	{
		return;
	}

	void* pVoid;
	vBuffer->Lock(0, 0, &pVoid, 0);
	memcpy(pVoid, vertices, sizeof(vertices));
	vBuffer->Unlock();

	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	pDevice->SetStreamSource(0, vBuffer, 0, sizeof(Vertex));
	pDevice->DrawPrimitive(D3DPT_LINESTRIP, 0, 4);
	vBuffer->Release();
}

void RenderEngine::RectFilled(const float x, const float y, const float x1, const float y1, const DWORD color) const
{
	Vertex vertices[] = {
		{ x,  y1, 0.5, 1, color },
		{ x,  y,  0.5, 1, color },
		{ x1, y1, 0.5, 1, color },
		{ x1, y,  0.5, 1, color }
	};

	LPDIRECT3DVERTEXBUFFER9 vBuffer = nullptr;
	if (FAILED(pDevice->CreateVertexBuffer(6 * sizeof(RenderEngine::Vertex), 0, D3DFVF_XYZRHW | D3DFVF_DIFFUSE,
		D3DPOOL_DEFAULT, &vBuffer, NULL)))
	{
		return;
	}

	void* pVoid;
	vBuffer->Lock(0, 0, &pVoid, 0);
	memcpy(pVoid, vertices, sizeof(vertices));
	vBuffer->Unlock();

	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	pDevice->SetStreamSource(0, vBuffer, 0, sizeof(Vertex));
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	vBuffer->Release();
}

void RenderEngine::RectFilled1(const float x, const float y, const float w, const float h, const DWORD color) const
{
	Vertex vertices[] = {
		{ x,     y + h, 0.5, 1, color },
		{ x,     y,     0.5, 1, color },
		{ x + w, y + h, 0.5, 1, color },
		{ x + w, y,     0.5, 1, color }
	};

	LPDIRECT3DVERTEXBUFFER9 vBuffer = nullptr;
	if (FAILED(pDevice->CreateVertexBuffer(6 * sizeof(RenderEngine::Vertex), 0, D3DFVF_XYZRHW | D3DFVF_DIFFUSE,
		D3DPOOL_DEFAULT, &vBuffer, NULL)))
	{
		return;
	}

	void* pVoid;
	vBuffer->Lock(0, 0, &pVoid, 0);
	memcpy(pVoid, vertices, sizeof(vertices));
	vBuffer->Unlock();

	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	pDevice->SetStreamSource(0, vBuffer, 0, sizeof(Vertex));
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	vBuffer->Release();
}

void RenderEngine::Circle(const float x, const float y, const float size, const int resolution, const DWORD color) const
{
	std::vector<Vertex> vertices(resolution + 2);

	for (int i = 0; i < resolution + 2; ++i)
	{
		vertices[i].x = x - size * cos(i * (2 * D3DX_PI / resolution));
		vertices[i].y = y - size * sin(i * (2 * D3DX_PI / resolution));
		vertices[i].color = color;
		vertices[i].z = 0.5;
		vertices[i].rhw = 1;
	}

	LPDIRECT3DVERTEXBUFFER9 v_buffer = nullptr;
	if (FAILED(
		pDevice->CreateVertexBuffer((resolution + 2) * sizeof(RenderEngine::Vertex), 0, D3DFVF_XYZRHW | D3DFVF_DIFFUSE,
			D3DPOOL_DEFAULT, &v_buffer, NULL)))
	{
		return;
	}

	void* pVoid;
	v_buffer->Lock(0, 0, &pVoid, 0);
	memcpy(pVoid, &vertices[0], (resolution + 2) * sizeof(Vertex));
	v_buffer->Unlock();

	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	pDevice->SetStreamSource(0, v_buffer, 0, sizeof(Vertex));
	pDevice->DrawPrimitive(D3DPT_LINESTRIP, 0, resolution);
	v_buffer->Release();
}

void RenderEngine::CircleFilled(const float x, const float y, const float size, const int resolution,
	const DWORD color) const
{
	std::vector<Vertex> vertices(resolution + 2);

	for (int i = 0; i < resolution + 2; ++i)
	{
		vertices[i].x = x - size * cos(i * (2 * D3DX_PI / resolution));
		vertices[i].y = y - size * sin(i * (2 * D3DX_PI / resolution));
		vertices[i].color = color;
		vertices[i].z = 0.5;
		vertices[i].rhw = 1;
	}

	LPDIRECT3DVERTEXBUFFER9 vBuffer = nullptr;
	if (FAILED(
		pDevice->CreateVertexBuffer((resolution + 2) * sizeof(RenderEngine::Vertex), 0, D3DFVF_XYZRHW | D3DFVF_DIFFUSE,
			D3DPOOL_DEFAULT, &vBuffer, NULL)))
		return;

	void* pVoid;
	vBuffer->Lock(0, 0, &pVoid, 0);
	memcpy(pVoid, &vertices[0], (resolution + 2) * sizeof(Vertex));
	vBuffer->Unlock();

	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	pDevice->SetStreamSource(0, vBuffer, 0, sizeof(Vertex));
	pDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, resolution);
	vBuffer->Release();
}

int RenderEngine::GetTextWidth(std::string& text, ID3DXFont* pFont)
{
	RECT rcRect = { 0, 0, 0, 0 };
	if (pFont)
	{
		const int strl = text.length();
		bool trailing = false;
		if (strl > 0 && text[strl - 1] == ' ')
		{
			trailing = true;
			text[strl - 1] = '.';
		}

		pFont->DrawTextA(nullptr, text.data(), strl, &rcRect, DT_CALCRECT | DT_SINGLELINE, D3DCOLOR_XRGB(0, 0, 0));

		if (trailing)
			text[strl - 1] = ' ';
	}

	return rcRect.right - rcRect.left;
}

int RenderEngine::GetTextHeight(std::string& text, ID3DXFont* pFont)
{
	RECT rcRect = { 0, 0, 0, 0 };
	if (pFont)
	{
		pFont->DrawTextA(nullptr, text.data(), text.length(), &rcRect, DT_CALCRECT, D3DCOLOR_XRGB(0, 0, 0));
	}

	return rcRect.bottom - rcRect.top;
}

int RenderEngine::GetTextWidth(std::wstring& text, ID3DXFont* pFont)
{
	RECT rcRect = { 0, 0, 0, 0 };
	if (pFont)
	{
		const int strl = text.length();
		bool trailing = false;
		if (strl > 0 && text[strl - 1] == ' ')
		{
			trailing = true;
			text[strl - 1] = '.';
		}

		pFont->DrawTextW(nullptr, text.data(), strl, &rcRect, DT_CALCRECT | DT_SINGLELINE, D3DCOLOR_XRGB(0, 0, 0));

		if (trailing)
			text[strl - 1] = ' ';
	}

	return rcRect.right - rcRect.left;
}

int RenderEngine::GetTextHeight(std::wstring& text, ID3DXFont* pFont)
{
	RECT rcRect = { 0, 0, 0, 0 };
	if (pFont)
	{
		pFont->DrawTextW(nullptr, text.data(), text.length(), &rcRect, DT_CALCRECT, D3DCOLOR_XRGB(0, 0, 0));
	}

	return rcRect.bottom - rcRect.top;
}

RenderEngine g_render;
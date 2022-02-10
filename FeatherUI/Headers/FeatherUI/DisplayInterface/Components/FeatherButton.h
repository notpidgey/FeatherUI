#pragma once

#include <functional>
#include <FeatherUI/DisplayInterface/FeatherComponent.h>

#include "FeatherLabel.h"

class FeatherButton : public FeatherComponent
{
public:
	FeatherButton(int x, int y, int width, int height,
		std::function<void(FeatherButton*)>, ID3DXFont* font, const std::string& buttonText,
		DWORD color = COLOR(255, 255, 255, 255));

	FeatherButton(int x, int y, int width, int height,
		std::function<void(FeatherButton*)>, ID3DXFont* font, const std::wstring& buttonText,
		DWORD color = COLOR(255, 255, 255, 255));

	FeatherButton(int x, int y, std::function<void(FeatherButton*)>, ID3DXFont* font, const std::string& buttonText,
		DWORD color = COLOR(255, 255, 255, 255));

	FeatherButton(int x, int y, std::function<void(FeatherButton*)>, ID3DXFont* font, const std::wstring& buttonText,
		DWORD color = COLOR(255, 255, 255, 255));

	void SetClickEvent(const std::function<void(FeatherButton*)>& function);

	void SetFillColor(D3DCOLOR color);

	void SetMouseClickColor(D3DCOLOR color);

	void SetOutlineColor(D3DCOLOR color);

protected:
	std::shared_ptr<FeatherLabel> label;
	std::function<void(FeatherButton*)> onClick;

	DWORD currentFill;
	DWORD fillColor = COLOR(255, 33, 33, 33);
	DWORD fillOnMousePress = COLOR(255, 22, 22, 22);
	DWORD outlineColor = COLOR(255, 22, 22, 22);

	void Render() override;

	void OnMousePressed(FeatherTouch* touch) override;

	void OnMouseUp(FeatherTouch* touch) override;
};

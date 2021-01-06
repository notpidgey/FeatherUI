#pragma once
#include <string>

#include "../control.h"

class textbox : public control
{
public:
	D3DCOLOR background_color = color(255,0,0,0);
	D3DCOLOR outline_color = color(255, 255, 0, 0);

	std::string content = "TEST STRING";
	ID3DXFont* font;
	bool active = false;

	textbox(float x, float y, float width, float height, ID3DXFont* font);
	
	void render() override;
	void handle_mouse() override;
};

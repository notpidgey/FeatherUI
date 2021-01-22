#pragma once
#include <Windows.h>
#include <memory>
#include <memory>
#include <string>
#include <vector>

#include "Controls/control.h"
#include "Controls/Headers/box.h"
#include "Controls/Headers/checkbox.h"
//#include "Controls/Headers/draggable_box.h"
#include "Controls/Headers/text_box.h"
#include "Controls/Headers/text.h"
#include "Controls/Headers/outline.h"
#include "Controls/Headers/slider.h"
#include "Utils/key_state_manager.h"

#include "../D3D/draw_func.h"

class user_interface
{
public:
	std::vector<std::unique_ptr<control>> controls;

	void add_control(control* control);
	std::unique_ptr<box> add_box(float x, float y, float width, float height, DWORD color, bool filled);
	std::unique_ptr<text> add_text(float x, float y, ID3DXFont* font, D3DCOLOR color, std::string text_string);
	std::unique_ptr<outline> add_outline(float x, float y, float width, float height, D3DCOLOR color);
	std::unique_ptr<checkbox> add_checkbox(float x, float y, float width, float height, bool* checked);
	//std::unique_ptr<draggable_box>* add_draggable_box(int x, int y, int width, int height, DWORD dword, bool filled, window* hwnd);
	std::unique_ptr<slider>* add_slider(float x, float y, float min, float max);

	void call_controls(HWND hwnd);

private:
	key_state_manager key_manager = {};
};

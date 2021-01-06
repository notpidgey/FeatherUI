#pragma once
#include <string>

#include "../control.h"
#include "../../Utils/key_state_manager.h"

class checkbox : public control
{
public:
	DWORD selected_color = color(255, 34, 34, 34);
	DWORD unselected_color = color(255, 51, 51, 51);
	DWORD outline_color = color(255, 0, 0, 0);
	
	float width_padding = 1.f;
	float height_padding = 1.f;
	bool* checked_ptr;

	checkbox(float x, float y, float width, float height, bool* checked);
	void add_text();

	void render() override;
	void handle_mouse() override;
};

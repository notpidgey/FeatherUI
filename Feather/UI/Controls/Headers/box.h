#pragma once
#include <Windows.h>

#include "../control.h"

class box : public control
{
public:
	DWORD color = color(255, 0, 0, 0);
	bool filled;

	box(float x, float y, float width, float height, DWORD color, bool filled);

	void render() override;
	void handle_mouse() override;
};

#pragma once
#include <Windows.h>
#include <WinUser.h>

struct vector2
{
	float x, y;
};

class key_state_manager
{
public:
	POINT mouse_pos;

	bool key_pressed(int key) noexcept;
	bool key_down(int key) noexcept;
	bool key_released(int key) noexcept;
	bool mouse_in_region(const int x, const int y, const int w, const int h);
	void poll_input(HWND* hwnd);
private:
	bool key_state[256];
	bool prev_key_state[256];
};
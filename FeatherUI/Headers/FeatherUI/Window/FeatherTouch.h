#pragma once
#include <Windows.h>

class Window;

class FeatherTouch
{
public:
	POINT mousePos;
	Window* window;

	bool KeyPressed(int key) noexcept;
	bool KeyDown(int key) noexcept;
	bool KeyReleased(int key) noexcept;
	bool MouseInRegion(int x, int y, int w, int h) const;
	bool MouseInRegion(const POINT& point, int w, int h) const;

	void PollInput(HWND* hwnd);

private:
	bool keyState[256] = {};
	bool prevKeyState[256] = {};
};
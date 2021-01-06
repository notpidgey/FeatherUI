#include "key_state_manager.h"

bool key_state_manager::key_pressed(int key) noexcept
{
    return key_state[key] == true && prev_key_state[key] == false;
}

bool key_state_manager::key_down(int key) noexcept
{
    return key_state[key] == true;
}

bool key_state_manager::key_released(int key) noexcept
{
    return key_state[key] == false && prev_key_state[key] == true;
}

// ReSharper disable once CppMemberFunctionMayBeConst
bool key_state_manager::mouse_in_region(const int x, const int y, const int w, const int h)
{
    return mouse_pos.x >= x && mouse_pos.y >= y && mouse_pos.x <= w + x && mouse_pos.y <= h + y;
}

void key_state_manager::poll_input(HWND* hwnd)
{
    for (int i = 0; i < 256; i++) {
        prev_key_state[i] = key_state[i];
        key_state[i] = GetAsyncKeyState(i);
    }

    POINT p;
    GetCursorPos(&p);
    ScreenToClient(*hwnd, &p);

    mouse_pos = { p.x,p.y };
}
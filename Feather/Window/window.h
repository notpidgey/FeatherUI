#pragma once
#include <Windows.h>

#include "Structs/font.h"
#include "../UI/user_interface.h"

class window
{
public:
    window(int i, int i1, unsigned long i2, const char* str, DWORD dword, const std::vector<font>& fonts, const font& font);
    ~window();
    
    user_interface user_interface;
    D3DCOLOR background_color;
    fonts fonts;
    HWND hwnd;

    int width;
    int height;
    int x;
    int y;
    const char* window_name;
    int window_flags;
    font title_font;

    void setup_window();
    void handle_message();
    void render();

private:
    DWORD LastFrameTime = 0;
    HINSTANCE hinstance;
    MSG message_ = {0};

    IDirect3D9Ex* pObject = nullptr;
    IDirect3DDevice9Ex* p_device_ = nullptr;
    D3DPRESENT_PARAMETERS p_params_ = {NULL};

    void init();

    void initialize_directx(const std::vector<font>& fonts);
};

#pragma once
#include <Windows.h>

#include "Structs/feather_font.h"
#include "../UI/user_interface.h"

class window
{
public:
    window(int width, int height, unsigned long flags, const char* window_name, DWORD background,
           const std::vector<feather_font>& fonts, const feather_font& font);
    ~window();
    
    user_interface u_interface;
    D3DCOLOR background_color;
    HWND hwnd;

    int width;
    int height;
    int x;
    int y;
    const char* win_name;
    int win_flags;
    feather_font title_font;

    void setup_window();
    void handle_message();
    void render();

private:
    DWORD last_frame_time_ = 0;
    HINSTANCE h_instance_;
    MSG message_ = {nullptr};

    IDirect3D9Ex* pObject = nullptr;
    IDirect3DDevice9Ex* p_device_ = nullptr;
    D3DPRESENT_PARAMETERS p_params_ = {NULL};

    void init();
    void initialize_directx(const std::vector<feather_font>& fonts);
};

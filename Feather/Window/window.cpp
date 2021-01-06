#include "WINDOW.h"
#include "../UI/Controls/Headers/title_bar.h"

window::window(int width, int height, unsigned long flags, const char* window_name, DWORD background,
               const std::vector<font>& fonts, const font& font)
{
    init();
    
    this->width = width;
    this->height = height;
    this->x = 0;
    this->y = 0;
    this->background_color = background;
    this->window_name = window_name;
    this->window_flags = flags;
    this->title_font = font;
    this->hwnd = CreateWindowExA(NULL, " ", window_name, window_flags, 0, 0, width, height, nullptr, nullptr, nullptr,
                                 nullptr);

    initialize_directx(fonts);
    setup_window();
}

window::~window()
{
    DestroyWindow(hwnd);
    UnregisterClassA("", hinstance);
}

void window::setup_window()
{
    UpdateWindow(hwnd);
    ShowWindow(hwnd, SW_SHOWDEFAULT);

    title_bar* dbox = new title_bar(0, 0, width, 30, color(255, 42, 42, 42), true, this);
    user_interface.add_control(dbox);
    user_interface.add_text(10, 6, *title_font.d3d_font, color(255, 255, 255, 255), "Feather UI");
}

void window::handle_message()
{
    while (PeekMessage(&message_, hwnd, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&message_);
        DispatchMessage(&message_);
    }
    render();
}

void window::initialize_directx(const std::vector<font>& fonts)
{
    ZeroMemory(&p_params_, sizeof(p_params_));

    Direct3DCreate9Ex(D3D_SDK_VERSION, &pObject);
    p_params_.Windowed = true;
    p_params_.SwapEffect = D3DSWAPEFFECT_DISCARD;
    p_params_.hDeviceWindow = hwnd;
    p_params_.BackBufferFormat = D3DFMT_A8R8G8B8;
    p_params_.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
    p_params_.BackBufferWidth = width;
    p_params_.BackBufferHeight = height;

    pObject->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &p_params_,
                            0,
                            &p_device_);

    draw.pDevice = p_device_;

    //create line object
    D3DXCreateLine(p_device_, &draw.pLine);

    for (auto& font : fonts)
    {
        D3DXCreateFontA(p_device_, font.font_size, 0, FW_REGULAR, 0, 0,
                        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
                        font.name.c_str(), font.d3d_font);
    }

    //set render states once
    p_device_->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
    p_device_->SetRenderState(D3DRS_ALPHATESTENABLE, false);
    p_device_->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, true);

    p_device_->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    p_device_->SetRenderState(D3DRS_SRCBLENDALPHA, D3DBLEND_INVDESTALPHA);
    p_device_->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    p_device_->SetRenderState(D3DRS_DESTBLENDALPHA, D3DBLEND_ONE);
    p_device_->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);

    //set free our direct x object
    pObject->Release();
}

void window::render()
{
    p_device_->Clear(0, NULL, D3DCLEAR_TARGET, background_color, 1.f, 0);
    if (p_device_->BeginScene() >= 0)
    {
        user_interface.call_controls(hwnd);

        p_device_->EndScene();
    }

    p_device_->Present(NULL, NULL, NULL, NULL);
}

void window::init()
{
    WNDCLASSEX wc = {0};

    hinstance = GetModuleHandle(nullptr);
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = DefWindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hinstance;
    wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wc.hbrBackground = nullptr;
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = L" ";

    RegisterClassEx(&wc);
}

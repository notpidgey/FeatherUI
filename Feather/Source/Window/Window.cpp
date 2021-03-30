#include <Window/Window.h>

#include "DisplayInterface/Components/FeatherWindowTitle.h"

Window::Window(const int width, const int height, const unsigned long flags, const char* windowName, const DWORD background, const std::vector<FeatherFont>& fonts, const FeatherFont& font)
{
    Init();

    this->width = width;
    this->height = height;
    this->position.x = 0;
    this->position.y = 0;
    this->backgroundColor = background;
    this->windowName = windowName;
    this->winFlags = flags;
    this->titleFont = font;
    this->hwnd = CreateWindowExA(NULL, " ", windowName, winFlags, 0, 0, width, height, nullptr, nullptr, nullptr, nullptr);
    this->keyStateManager.window = this;

    InitializeDirectx(fonts);
    SetupWindow();
}

Window::~Window()
{
    DestroyWindow(hwnd);
    UnregisterClassA("", hInstance);
}

void Window::SetupWindow()
{
    UpdateWindow(hwnd);
    ShowWindow(hwnd, SW_SHOWDEFAULT);

    container.AddControl(new FeatherWindowTitle(0, 0, width, 30, COLOR(255, 0, 0, 0), windowName));
}

void Window::HandleMessage()
{
    while (PeekMessage(&message, hwnd, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    Render();
}

void Window::InitializeDirectx(const std::vector<FeatherFont>& fonts)
{
    ZeroMemory(&pParams, sizeof(pParams));

    Direct3DCreate9Ex(D3D_SDK_VERSION, &pObject);
    pParams.Windowed = true;
    pParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
    pParams.hDeviceWindow = hwnd;
    pParams.BackBufferFormat = D3DFMT_A8R8G8B8;
    pParams.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
    pParams.BackBufferWidth = width;
    pParams.BackBufferHeight = height;

    pObject->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &pParams,nullptr, &pDevice);
    g_render.pDevice = pDevice;

    for (auto& font : fonts)
    {
        D3DXCreateFontA(pDevice, font.fontSize, 0, FW_REGULAR, 0, 0,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
            font.name.c_str(), font.d3dFont);
    }

    pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
    pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
    pDevice->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, true);
    pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    pDevice->SetRenderState(D3DRS_SRCBLENDALPHA, D3DBLEND_INVDESTALPHA);
    pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    pDevice->SetRenderState(D3DRS_DESTBLENDALPHA, D3DBLEND_ONE);
    pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);

    pObject->Release();
}

void Window::Render()
{
    pDevice->Clear(0, nullptr, D3DCLEAR_TARGET, backgroundColor, 1.f, 0);

    if (pDevice->BeginScene() >= 0)
    {
        keyStateManager.PollInput(&hwnd);

        container.HandleInput(&keyStateManager);
        container.Render();

        pDevice->EndScene();
    }

    pDevice->Present(nullptr, nullptr, nullptr, nullptr);
}

void Window::Init()
{
    WNDCLASSEX wc = {0};

    hInstance = GetModuleHandle(nullptr);
    wc.cbSize = sizeof WNDCLASSEX;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = DefWindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wc.hbrBackground = nullptr;
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = L" ";
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);

    RegisterClassEx(&wc);
}

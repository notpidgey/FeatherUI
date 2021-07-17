#pragma once
#include <mutex>
#include <vector>
#include <Windows.h>
#include <Graphics/DirectX9/Structs/FeatherFont.h>
#include <DisplayInterface/Components/FeatherContainer.h>
#include <concurrent_queue.h>
#include <functional>

#include "Util/ConcurrentQueue.h"

class Window
{
public:
    Window(int width, int height, unsigned long flags, const std::string& windowName, DWORD background);
    ~Window();

    void InitializeDirectX(const std::vector<FeatherFont>& fonts);
    
    std::shared_ptr<FeatherContainer> container;
    FeatherTouch keyStateManager;
    FeatherFont titleFont;
    
    D3DCOLOR backgroundColor;
    POINT position;
    HWND hwnd;

    moodycamel::ConcurrentQueue<std::function<void()>> postRenderQueue;
 
    std::string windowName;
    int width;
    int height;
    int winFlags;

    void SetupWindow() const;
    void HandleMessage();
    void Render();


private:
    IDirect3D9Ex* pObject = nullptr;
    IDirect3DDevice9Ex* pDevice = nullptr;
    D3DPRESENT_PARAMETERS pParams = {NULL};
    
    DWORD lastFrameTime = 0;
    HINSTANCE hInstance;
    MSG message = {nullptr};

    
    void Init();
    void InitializeDirectx(const std::vector<FeatherFont>& fonts);
};

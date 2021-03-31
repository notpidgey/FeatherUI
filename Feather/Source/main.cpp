#include <iostream>
#include <Window/Window.h>
#include <Graphics/DirectX9/RenderEngine.h>
#include <DisplayInterface/Components/FeatherWindowTitle.h>

ID3DXFont* g_tahoma16Px = nullptr;
ID3DXFont* g_montserrat16Px = nullptr;
const char* g_windowName = "Feather UI";

int main()
{
    const std::vector fonts
    {
        FeatherFont(&g_tahoma16Px, "Tahoma", 16),
        FeatherFont(&g_montserrat16Px, "Montserrat", 16)
    };

    Window main(750, 430, WS_POPUP, "Feather",COLOR(255, 255, 255, 255), fonts, FeatherFont(&g_montserrat16Px, "Montserrat", 16));
    FeatherContainer* canvas = &main.container;
    canvas->AddControl(new FeatherWindowTitle(0, 0, 750, 30, COLOR(255, 42, 42, 42), g_tahoma16Px, g_windowName));

    while(TRUE)
        main.HandleMessage();
}

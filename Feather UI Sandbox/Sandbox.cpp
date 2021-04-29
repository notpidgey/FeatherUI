#include <iostream>
#include <vector>

#include <DisplayInterface/Components/FeatherContainer.h>
#include <DisplayInterface/Components/FeatherWindowTitle.h>
#include <Graphics/DirectX9/RenderEngine.h>

#include <Window/Window.h>

ID3DXFont* tahoma16Px = nullptr;
ID3DXFont* tahoma12Px = nullptr;
ID3DXFont* montserrat16Px = nullptr;

int main()
{
    std::vector<FeatherFont> fonts
    {
        FeatherFont(&tahoma16Px, "Tahoma", 16),
        FeatherFont(&tahoma12Px, "Tahoma", 12),
        FeatherFont(&montserrat16Px, "Montserrat", 16)
    };

    std::string windowTitle = "Feather Sandbox";
    
    Window window(1280, 720, WS_POPUP, "Feather",COLOR(255, 255, 255, 255), fonts, fonts.at(2));
    std::shared_ptr<FeatherComponent> container = window.container->AddControl(
        std::make_shared<FeatherWindowTitle>(0, 0, 1280, 30, COLOR(255, 42, 42, 42), tahoma16Px, windowTitle)
    );

    //window.container->RemoveControl(container);
    
    while(true)
        window.HandleMessage();
}
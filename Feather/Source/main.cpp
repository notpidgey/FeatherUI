#include <DisplayInterface/Components/FeatherCheckbox.h>
#include <DisplayInterface/Components/FeatherWindowTitle.h>
#include <DisplayInterface/Components/FeatherButton.h>
#include <DisplayInterface/Components/FeatherSlider.h>

#include <Window/Window.h>
#include <Graphics/DirectX9/RenderEngine.h>

#include <Windows.h>
#include <iostream>
#include <stdint.h>

#include "DisplayInterface/Components/FeatherTabView.h"
#include "DisplayInterface/Components/FeatherTextBox.h"

ID3DXFont* g_tahoma16Px = nullptr;
ID3DXFont* g_tahoma12Px = nullptr;
ID3DXFont* g_montserrat16Px = nullptr;

std::string g_windowTitle = "Feather UI";
bool g_checked = true;

void OnClick(FeatherButton* button)
{
    std::cout << "The Button Was Clicked!" << std::endl;
}

int main()
{
    const std::vector fonts
    {
        FeatherFont(&g_tahoma16Px, "Tahoma", 16),
        FeatherFont(&g_tahoma12Px, "Tahoma", 12),
        FeatherFont(&g_montserrat16Px, "Montserrat", 16)
    };

    Window main(750, 430, WS_POPUP, "Feather",COLOR(255, 255, 255, 255), fonts, FeatherFont(&g_montserrat16Px, "Montserrat", 16));
    FeatherContainer* canvas = &main.container;
    
    canvas->AddControl(new FeatherWindowTitle(0, 0, 750, 30, COLOR(255, 42, 42, 42), g_tahoma16Px, g_windowTitle.data()));

    FeatherTabView* tabMenu = static_cast<FeatherTabView*>(
        canvas->AddControl(new FeatherTabView(0, 30, 750, 400, 25, g_tahoma16Px, std::vector({"Yes", "No", "Maybe"})))
    );

    tabMenu->AddToTab(new FeatherCheckbox(10, 10, &g_checked, g_tahoma16Px, "Check this checkbox!", COLOR(255, 0, 0, 0)), 0);
    tabMenu->AddToTab(new FeatherTextBox(10, 40, 200, 22, g_tahoma16Px, "Placeholder"), 0);
    tabMenu->AddToTab(new FeatherButton(10, 10, &OnClick, g_tahoma16Px, "Some Cool Text!", COLOR(255, 255, 255, 255)), 1);
    tabMenu->AddToTab(new FeatherSlider(10, 10, 150, FeatherSlider::PERCENTAGE, 42, 7362, g_tahoma12Px, "Some Slider"), 2);

    tabMenu->SetActiveTab(0);
    
    while (true)
    {
        main.HandleMessage();
    }
}

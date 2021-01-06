#include <iostream>
#include "UI/Controls/Headers/checkbox.h"
#include "UI/Controls/Headers/textbox.h"
#include "UI/Controls/Headers/title_bar.h"
#include "UI/Controls/Headers/slider.h"

#include "Window/WINDOW.h"
#include "D3D/draw_func.h"

ID3DXFont* tahoma16_px = nullptr;
ID3DXFont* montserrat18_px = nullptr;
bool checked = true;

int main()
{
    std::vector<font> fonts;
    fonts.push_back(font(&tahoma16_px, "Tahoma", 16));
    fonts.push_back(font(&montserrat18_px, "Montserrat", 16));
    
    window main_window(750, 430, WS_POPUP , "Feather",
                       color(255, 255, 255, 255), fonts, font(&montserrat18_px, "Montserrat", 16));


    //TODO: Fix recursive inclusion in UserInterface and Window 
    main_window.user_interface.add_outline(0, 30, 750, 400, color(255, 0, 0, 0));
    main_window.user_interface.add_outline(12, 75, 728, 345, color(255, 0, 0, 0));
    main_window.user_interface.add_checkbox(12, 47, 110, 29, &checked);

    //Combination
    main_window.user_interface.add_text(20, 82, tahoma16_px, color(255, 0, 0, 0), "Slider");
    main_window.user_interface.add_slider(20,102,-69,100);

    while (true)
    {
        main_window.handle_message();
    }
}

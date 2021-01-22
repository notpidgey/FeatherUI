#include <iostream>
#include "UI/Controls/Headers/checkbox.h"
#include "UI/Controls/Headers/text_box.h"
#include "UI/Controls/Headers/title_bar.h"
#include "UI/Controls/Headers/slider.h"

#include "Window/WINDOW.h"
#include "D3D/draw_func.h"

ID3DXFont* tahoma16_px = nullptr;
ID3DXFont* montserrat16_px = nullptr;
bool checked = true;

int main()
{
    const std::vector<feather_font> fonts
    {
        feather_font(&tahoma16_px, "Tahoma", 16),
        feather_font(&montserrat16_px, "Montserrat", 16)
    };

    window main(750, 430, WS_POPUP, "Feather",
                color(255, 255, 255, 255), fonts, feather_font(&montserrat16_px, "Montserrat", 16));

    main.u_interface.add_outline(0, 30, 750, 400, color(255, 0, 0, 0));
    main.u_interface.add_outline(12, 75, 728, 345, color(255, 0, 0, 0));
    main.u_interface.add_checkbox(12, 47, 110, 29, &checked);

    //Combination
    main.u_interface.add_text(20, 82, tahoma16_px, color(255, 0, 0, 0), "Slider");
    main.u_interface.add_slider(20, 102, -69, 100);

    while (true)
    {
        main.handle_message();
    }
}

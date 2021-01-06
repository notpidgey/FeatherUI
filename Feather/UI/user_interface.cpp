#include "user_interface.h"

void user_interface::add_control(control* control)
{
    controls.emplace_back(control);
    control->k_manager = &key_manager;
}

std::unique_ptr<box> user_interface::add_box(float x, float y, float width, float height, DWORD color, bool filled)
{
    box button(x, y, width, height, color, filled);
    button.k_manager = &key_manager;

    std::unique_ptr<box> unique = std::make_unique<class box>(button);
    controls.emplace_back(std::move(unique));

    return unique;
}

std::unique_ptr<text> user_interface::add_text(float x, float y, ID3DXFont* font, D3DCOLOR color,
                                              std::string text_string)
{
    text textcontrol(x, y, font, text_string, color);
    textcontrol.k_manager = &key_manager;

    std::unique_ptr<text> unique = std::make_unique<class text>(textcontrol);
    controls.emplace_back(std::move(unique));

    return unique;
}

std::unique_ptr<outline> user_interface::add_outline(float x, float y, float width, float height,
                                                    D3DCOLOR color = color(255, 255, 255, 255))
{
    outline line(x, y, width, height, color);
    line.k_manager = &key_manager;

    std::unique_ptr<outline> unique = std::make_unique<class outline>(line);
    controls.emplace_back(std::move(unique));

    return unique;
}

std::unique_ptr<checkbox> user_interface::add_checkbox(float x, float y, float width, float height, bool* checked)
{
    checkbox cbox(x, y, width, height, checked);
    cbox.k_manager = &key_manager;

    std::unique_ptr<checkbox> unique = std::make_unique<class checkbox>(cbox);
    controls.emplace_back(std::move(unique));

    return unique;
}


//TODO: Fix recursive inclusion in UserInterface and Window
/*
std::unique_ptr<draggable_box>* UserInterface::add_draggable_box(int x, int y, int width, int height, DWORD dword,
    bool filled,
    window* hwnd)
    {
    draggable_box draggable(x, y, width, height, dword, filled, hwnd);
    std::unique_ptr<draggable_box> unique = std::make_unique<class draggable_box>(draggable);
    controls.emplace_back(unique);

    return &unique;
}
*/


std::unique_ptr<slider> user_interface::add_slider(float x, float y, float min, float max)
{
    slider sliding_bar(x, y, min, max);
    sliding_bar.k_manager = &key_manager;

    std::unique_ptr<slider> unique = std::make_unique<class slider>(sliding_bar);
    controls.emplace_back(std::move(unique));

    return unique;
}

void user_interface::call_controls(HWND hwnd)
{
    key_manager.poll_input(&hwnd);

    for (const auto& control : controls)
    {
        if (control->should_render)
        {
            control->render();
            control->handle_mouse();
        }
    }
}

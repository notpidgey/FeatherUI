#pragma once
#include "../../D3D/draw_func.h"
#include "../Utils/key_state_manager.h"

class control
{
public:
	virtual ~control() = default;
	bool should_render = true;
	float x{};
	float y{};
	float w{};
	float h{};

	virtual void render() = 0;
	virtual void handle_mouse() = 0;

	key_state_manager* k_manager;
};

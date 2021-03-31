// ReSharper disable CppFunctionIsNotImplemented
#pragma once

#include <DisplayInterface/FeatherForwards.h>
#include <Graphics/DirectX9/RenderEngine.h>
#include <Window/FeatherTouch.h>
#include <Windef.h>

class FeatherComponent
{
public:
    virtual ~FeatherComponent() = default;

    FeatherComponent* parent = nullptr;
    FeatherContainer* childrenContainer = nullptr;
    
    POINT truePosition{};
    POINT vPosition{};
    float opacity = 1.f;
    bool mouseInRegion = false;
    int width = 100;
    int height = 20;

    POINT GetTruePosition(int xOffset, int yOffset) const;
    virtual void HandleInput(FeatherTouch* touch) const;
    
    //Implemented Events
    virtual void Render();

    //Implemented Input Events
    virtual void OnEnter(FeatherTouch* touch) {};
    virtual void OnLeave(FeatherTouch* touch) {};

    virtual void OnHover(FeatherTouch* touch) {};

    virtual void OnMouseAway(FeatherTouch* touch) {};

    virtual void OnMouseDown(FeatherTouch* touch) {};
    virtual void OnMouseUp(FeatherTouch* touch) {};
};
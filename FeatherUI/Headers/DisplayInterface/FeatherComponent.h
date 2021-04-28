// ReSharper disable CppFunctionIsNotImplemented
#pragma once
#include <memory>
#include <DisplayInterface/FeatherForwards.h>
#include <Graphics/DirectX9/RenderEngine.h>
#include <Window/FeatherTouch.h>
#include <Windef.h>

class FeatherComponent
{
public:
    virtual ~FeatherComponent() = default;

    std::weak_ptr<FeatherComponent> parent;
    std::shared_ptr<FeatherComponent> shared = std::shared_ptr<FeatherComponent>(this);
    std::unique_ptr<FeatherContainer> childrenContainer = nullptr;
    
    POINT tPosition {};
    POINT vPosition {};
    bool render = true;
    bool mouseInRegion = false;
    bool handlingMouseDownEvent = false;
    int width = 0;
    int height = 0;

    POINT GetTruePosition(FeatherComponent* component, int xOffset, int yOffset) const;
    virtual void SetPosition(int x, int y);

    virtual void FixPosition(int x, int y);
    virtual void HandleInput(FeatherTouch* touch);
    
    //Implemented Events
    virtual void Render();

    //Implemented Input Events
    virtual void OnEnter(FeatherTouch* touch) {};
    virtual void OnLeave(FeatherTouch* touch) {};

    virtual void OnHover(FeatherTouch* touch) {};

    virtual void OnMouseAway(FeatherTouch* touch) {};
    virtual void OnMousePressed(FeatherTouch* touch) {};
    virtual void OnMouseDown(FeatherTouch* touch) {};
    virtual void OnMouseUp(FeatherTouch* touch) {};
};
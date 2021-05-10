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
    virtual ~FeatherComponent();

    int GetX() const;
    int GetY() const;
    int GetTrueX() const;
    int GetTrueY() const;
    int GetWidth() const;
    int GetHeight() const;
    bool GetRenderState() const;
    POINT GetPosition() const;
    POINT GetTruePosition(FeatherComponent* component, int xOffset, int yOffset) const;

    void SetX(int x);
    void SetY(int y);
    void SetPosition(int x, int y);
    void SetWidth(int width);
    void SetHeight(int height);
    void SetDimensions(int x, int y, int width, int height);
    void SetRenderState(bool renderState);
    void SetParent(std::shared_ptr<FeatherComponent> component);

    void SetMouseInRegion(bool mouseInRegion);
    bool MouseInRegion() const;
    void SetHandlingMouseDownEvent(bool handlingMouseDownEvent);
    bool HandlingMouseDownEvent() const;
    
    //Implemented for container
    virtual void Render();
    virtual void FixPosition(int x, int y);
    virtual void HandleInput(FeatherTouch* touch);

    //Implemented Input Events
    virtual void OnEnter(FeatherTouch* touch) {};
    virtual void OnLeave(FeatherTouch* touch) {};

    virtual void OnHover(FeatherTouch* touch) {};

    virtual void OnMouseAway(FeatherTouch* touch) {};
    virtual void OnMousePressed(FeatherTouch* touch) {};
    virtual void OnMouseDown(FeatherTouch* touch) {};
    virtual void OnMouseUp(FeatherTouch* touch) {};

protected:
    std::weak_ptr<FeatherComponent> parent;
    std::shared_ptr<FeatherComponent> shared = std::shared_ptr<FeatherComponent>(this);
    std::unique_ptr<FeatherContainer> childrenContainer = nullptr;
    
    POINT tPosition {};
    POINT vPosition {};
    
    bool render = true;
    int width = 0;
    int height = 0;

    bool mouseInRegion = false;
    bool handlingMouseDownEvent = false;
};
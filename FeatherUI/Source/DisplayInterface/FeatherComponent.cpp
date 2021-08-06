#include <DisplayInterface/FeatherComponent.h>
#include <DisplayInterface/Components/FeatherContainer.h>

FeatherComponent::~FeatherComponent()
{
    this->shared.reset();
}

int FeatherComponent::GetX() const
{
    return vPosition.x;
}

int FeatherComponent::GetY() const
{
    return vPosition.y;
}

int FeatherComponent::GetTrueX() const
{
    return tPosition.x;
}

int FeatherComponent::GetTrueY() const
{
    return tPosition.y;
}

int FeatherComponent::GetWidth() const
{
    return width;
}

int FeatherComponent::GetHeight() const
{
    return height;
}

bool FeatherComponent::GetRenderState() const
{
    return render;
}

POINT FeatherComponent::GetTruePosition(FeatherComponent* component, const int xOffset = 0, const int yOffset = 0) const
{
    int totalX = 0;
    int totalY = 0;

    std::shared_ptr<FeatherComponent> nextParent = component->parent.lock();
    while (nextParent)
    {
        totalX += nextParent->vPosition.x;
        totalY += nextParent->vPosition.y;

        nextParent = nextParent->parent.lock();
    }

    return {totalX + xOffset, totalY + yOffset};
}

void FeatherComponent::SetComponentWindow(Window* window)
{
    this->window = window;
    if(childrenContainer != nullptr)
    {
        childrenContainer->SetComponentWindow(window);
    }
}

void FeatherComponent::SetPosition(const int x, const int y)
{
    this->vPosition.x = x;
    this->vPosition.y = y;
}

void FeatherComponent::SetDimensions(const int x, const int y, const int width, const int height)
{
    this->vPosition.x = x;
    this->vPosition.y = y;
    this->width = width;
    this->height = height;
}
void FeatherComponent::SetRenderState(const bool renderState)
{
    this->render = renderState;
}

void FeatherComponent::SetParent(const std::shared_ptr<FeatherComponent> component)
{
    this->parent = component;
}

void FeatherComponent::SetMouseInRegion(const bool mouseInRegion)
{
    this->mouseInRegion = mouseInRegion;
}

bool FeatherComponent::MouseInRegion() const
{
    return mouseInRegion;
}

void FeatherComponent::SetHandlingMouseDownEvent(const bool handlingMouseDownEvent)
{
    this->handlingMouseDownEvent = handlingMouseDownEvent;
}

bool FeatherComponent::HandlingMouseDownEvent() const
{
    return handlingMouseDownEvent;
}

POINT FeatherComponent::GetPosition() const
{
    return vPosition;
}

void FeatherComponent::SetX(const int x)
{
    this->vPosition.x = x;
}

void FeatherComponent::SetY(const int y)
{
    this->vPosition.y = y;
}

void FeatherComponent::SetHeight(const int height)
{
    this->height = height;
}

void FeatherComponent::SetWidth(const int width)
{
    this->width = width;
}

void FeatherComponent::FixPosition(const int x, const int y)
{
    this->tPosition.x = x + vPosition.x;
    this->tPosition.y = y + vPosition.y;

    if (childrenContainer != nullptr)
    {
        childrenContainer->FixPosition(this->tPosition.x, this->tPosition.y);
    }
}

void FeatherComponent::HandleInput(FeatherTouch* touch)
{
    if (childrenContainer != nullptr)
    {
        if (childrenContainer->render)
            childrenContainer->HandleInput(touch);
    }
}

void FeatherComponent::Render()
{
    if (childrenContainer->render)
        childrenContainer->Render();
}

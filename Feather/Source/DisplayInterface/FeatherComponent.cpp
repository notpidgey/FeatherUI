#include <DisplayInterface/FeatherComponent.h>
#include <DisplayInterface/Components/FeatherContainer.h>

POINT FeatherComponent::GetTruePosition(FeatherComponent* component, const int xOffset = 0, const int yOffset = 0) const
{
    int totalX = 0;
    int totalY = 0;

    FeatherComponent* nextParent = component->parent;
    while (nextParent != nullptr)
    {
        totalX += nextParent->vPosition.x;
        totalY += nextParent->vPosition.y;

        nextParent = nextParent->parent;
    }

    return {totalX + xOffset, totalY + yOffset};
}

void FeatherComponent::SetPosition(const int x, const int y)
{
    this->vPosition.x = x;
    this->vPosition.y = y;
}

void FeatherComponent::HandleInput(FeatherTouch* touch)
{
    if (childrenContainer != nullptr)
        childrenContainer->HandleInput(touch);
}

void FeatherComponent::Render()
{
    childrenContainer->Render();
}

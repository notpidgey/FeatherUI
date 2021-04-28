#include <DisplayInterface/FeatherComponent.h>
#include <DisplayInterface/Components/FeatherContainer.h>

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

void FeatherComponent::SetPosition(const int x, const int y)
{
    this->vPosition.x = x;
    this->vPosition.y = y;
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

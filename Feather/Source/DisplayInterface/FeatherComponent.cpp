#include <DisplayInterface/FeatherComponent.h>
#include <DisplayInterface/Components/FeatherContainer.h>

POINT FeatherComponent::GetTruePosition(const int xOffset = 0, const int yOffset = 0) const
{
    int totalX = 0;
    int totalY = 0;

    FeatherComponent* nextParent = this->parent;
    while (nextParent != nullptr)
    {
        totalX += nextParent->vPosition.x;
        totalY += nextParent->vPosition.y;

        nextParent = nextParent->parent;
    }

    return {totalX + xOffset, totalY + yOffset};
}

void FeatherComponent::HandleInput(FeatherTouch* touch) const
{
    if (childrenContainer != nullptr)
        for (FeatherComponent* childComponent : childrenContainer->children)
        {
            const auto [x, y] = GetTruePosition(childComponent->vPosition.x, childComponent->vPosition.y);

            childComponent->truePosition.x = x;
            childComponent->truePosition.y = y;

            if (touch->MouseInRegion(x, y, childComponent->width, childComponent->height))
            {
                if (!childComponent->mouseInRegion)
                {
                    childComponent->mouseInRegion = true;
                    childComponent->OnEnter(touch);
                }

                if (touch->KeyDown(VK_LBUTTON))
                {
                    childComponent->OnMouseDown(touch);
                }
                else
                {
                    childComponent->OnMouseUp(touch);
                }

                childComponent->OnHover(touch);
            }
            else if (childComponent->mouseInRegion)
            {
                childComponent->mouseInRegion = false;
                childComponent->OnLeave(touch);
            }
            
            childComponent->HandleInput(touch);
        }
}

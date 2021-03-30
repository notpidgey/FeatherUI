#include <memory>
#include <DisplayInterface/Components/FeatherContainer.h>

FeatherComponent* FeatherContainer::AddControl(FeatherComponent* control)
{
    children.push_back(control);

    return control;
}

void FeatherContainer::HandleInput(FeatherTouch* touch) const 
{
    for (FeatherComponent* childComponent : children)
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

void FeatherContainer::Render()
{
    for (FeatherComponent* child : children)
    {
        child->Render();
    }
}

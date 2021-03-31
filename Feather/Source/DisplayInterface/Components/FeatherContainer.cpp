#include <memory>
#include <DisplayInterface/Components/FeatherContainer.h>

FeatherComponent* FeatherContainer::AddControl(FeatherComponent* component)
{
    component->parent = parent;
    children.push_back(component);

    return component;
}

void FeatherContainer::HandleInput(FeatherTouch* touch) 
{
    for (FeatherComponent* childComponent : children)
    {
        const auto [x, y] = GetTruePosition(childComponent, childComponent->vPosition.x, childComponent->vPosition.y);
        
        childComponent->tPosition.x = x;
        childComponent->tPosition.y = y;
        
        if (touch->MouseInRegion(x, y, childComponent->width, childComponent->height))
        {
            if (!childComponent->mouseInRegion)
            {
                childComponent->mouseInRegion = true;
                childComponent->OnEnter(touch);
            }

            if(touch->KeyPressed(VK_LBUTTON))
            {
                childComponent->handlingMouseDownEvent = true;
                childComponent->OnMousePressed(touch);
            }   
            if (touch->KeyDown(VK_LBUTTON))
            {
                childComponent->handlingMouseDownEvent = true;
                childComponent->OnMouseDown(touch);
            }
            else if (touch->KeyReleased(VK_LBUTTON))
            {
                childComponent->handlingMouseDownEvent = false;
                childComponent->OnMouseUp(touch);
            }

            childComponent->OnHover(touch);
        }
        else if (childComponent->mouseInRegion)
        {
            childComponent->mouseInRegion = false;
            childComponent->OnLeave(touch);
        }

        if(childComponent->handlingMouseDownEvent)
        {
            if (touch->KeyReleased(VK_LBUTTON))
            {
                childComponent->handlingMouseDownEvent = false;
                childComponent->OnMouseUp(touch);
            }
        }

        childComponent->HandleInput(touch);
    }    
}

void FeatherContainer::HandleInput(FeatherTouch* touch, FeatherComponent* childComponent)
{


}

void FeatherContainer::Render()
{
    for (FeatherComponent* child : children)
    {
        child->Render();
    }
}

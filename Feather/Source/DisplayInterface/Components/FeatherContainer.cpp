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

            if (touch->KeyPressed(VK_LBUTTON))
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

        if (childComponent->handlingMouseDownEvent)
        {
            if (touch->KeyReleased(VK_LBUTTON))
            {
                childComponent->handlingMouseDownEvent = false;
                childComponent->OnMouseUp(touch);
            }
            else
            {
                childComponent->OnMouseAway(touch);
            }
        }

        childComponent->HandleInput(touch);
    }
}

void FeatherContainer::Render()
{
    RECT rect;
    
    for (FeatherComponent* child : children)
    {
        if(parent != nullptr)
        {
            rect = {
                parent->tPosition.x ,parent->tPosition.y,
                parent->tPosition.x + parent->width,parent->tPosition.y + parent->height,
            };
        }
        else
        {
            rect = {
                0,0,
                g_render.deviceWidth, g_render.deviceHeight
            };
        }
        
        g_render.pDevice->SetScissorRect(&rect);
        
        child->Render();

        g_render.Rect1(child->tPosition.x, child->tPosition.y, child->width, child->height, COLOR(255,0,255,0));
    }
}

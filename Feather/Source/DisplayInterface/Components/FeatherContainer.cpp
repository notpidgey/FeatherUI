#include <algorithm>
#include <DisplayInterface/Components/FeatherContainer.h>

FeatherComponent* FeatherContainer::AddControl(FeatherComponent* component)
{
    component->parent = this;
    children.push_back(component);

    return component;
}

void FeatherContainer::ClampRect(FeatherComponent* child, RECT* currentScissor)
{
    RECT clampedScissor;

    clampedScissor = {
        std::clamp(child->tPosition.x, currentScissor->left, currentScissor->right),
        std::clamp(child->tPosition.y, currentScissor->top, currentScissor->bottom),
        std::clamp(child->tPosition.x + child->width, currentScissor->left, currentScissor->right),
        std::clamp(child->tPosition.y + child->height, currentScissor->top, currentScissor->bottom)
    };

    g_render.Rect1(clampedScissor.left, clampedScissor.top, clampedScissor.right-clampedScissor.left, clampedScissor.bottom - clampedScissor.top, COLOR(255, 0, 255, 0));
    g_render.pDevice->SetScissorRect(&clampedScissor);
}

void FeatherContainer::Transform(const int x, const int y)
{
    this->vPosition.x += x;
    this->vPosition.y += y;
    this->vPosition.x = std::clamp((int)vPosition.x, 0, parent->width);
    this->vPosition.y = std::clamp((int)vPosition.y, 0, parent->height);

    this->width = parent->width - vPosition.x;
    this->height = parent->height - vPosition.y;
}

void FeatherContainer::FixPosition(const int x, const int y)
{
    this->tPosition.x = x + vPosition.x;
    this->tPosition.y = y + vPosition.y;

    for (FeatherComponent* child : children)
    {
        child->FixPosition(this->tPosition.x, this->tPosition.y);
    }
}

void FeatherContainer::HandleInput(FeatherTouch* touch)
{
    for (FeatherComponent* childComponent : children)
    {
        if (childComponent->render)
        {
            if (touch->MouseInRegion(childComponent->tPosition.x, childComponent->tPosition.y, childComponent->width, childComponent->height))
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
}

void FeatherContainer::Render()
{
    RECT rect;
    g_render.pDevice->GetScissorRect(&rect);

    for (FeatherComponent* child : children)
    {
        if (child->render)
        {
            if (this->parent != nullptr)
            {
                ClampRect(child, &rect);
            }
            else
            {
                rect = {
                    0, 0,
                    g_render.deviceWidth, g_render.deviceHeight
                };

                g_render.pDevice->SetScissorRect(&rect);
            }

            child->Render();        
        }
    }
}

void FeatherContainer::SetInitialProperties()
{
    this->width = parent->width;
    this->height = parent->height;
}

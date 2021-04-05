#include <algorithm>
#include <DisplayInterface/Components/FeatherContainer.h>

FeatherComponent* FeatherContainer::AddControl(FeatherComponent* component)
{
    component->parent = this;
    children.push_back(component);

    return component;
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
    for (FeatherComponent* child : children)
    {
        if (child->render)
        {
            if (this->parent != nullptr)
            {
                rect = {
                    this->tPosition.x, this->tPosition.y,
                    this->tPosition.x + this->width, this->tPosition.y + this->height,
                };
            }
            else
            {
                rect = {
                    0, 0,
                    g_render.deviceWidth, g_render.deviceHeight
                };
            }

            g_render.pDevice->SetScissorRect(&rect);

            child->Render();

            //g_render.Rect1(child->tPosition.x, child->tPosition.y, child->width, child->height, COLOR(255, 0, 255, 0));
        }
    }
}

void FeatherContainer::SetInitialProperties()
{
    this->width = parent->width;
    this->height = parent->height;
}

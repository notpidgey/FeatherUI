#include <algorithm>
#include <DisplayInterface/Components/FeatherContainer.h>

FeatherContainer::FeatherContainer()
{ }

FeatherContainer::FeatherContainer(const std::shared_ptr<FeatherComponent>& parent)
{
    this->parent = std::weak_ptr(parent);
    SetInitialProperties();
}

FeatherContainer::FeatherContainer(const std::shared_ptr<FeatherComponent>& parent, FeatherComponent* child)
{
    this->parent = std::weak_ptr(parent);
    SetInitialProperties();

    AddControl(child);
}

FeatherContainer::FeatherContainer(const std::shared_ptr<FeatherComponent>& parent, FeatherComponent* child1, FeatherComponent* child2)
{
    this->parent = std::weak_ptr(parent);
    SetInitialProperties();

    AddControl(child1);
    AddControl(child2);
}

FeatherContainer::FeatherContainer(const std::shared_ptr<FeatherComponent>& parent, FeatherComponent* child1, FeatherComponent* child2, FeatherComponent* child3)
{
    this->parent = std::weak_ptr(parent);
    SetInitialProperties();

    AddControl(child1);
    AddControl(child2);
    AddControl(child3);
}

FeatherComponent* FeatherContainer::AddControl(FeatherComponent* component)
{
    component->parent = shared;
    children.push_back(std::unique_ptr<FeatherComponent>(component));

    return component;
}

bool FeatherContainer::RemoveControl(FeatherComponent* component)
{
    auto itr = std::find_if(
        std::begin(children),
        std::end(children),
        [component](auto& element){ return element.get() == component; });

    if (itr != children.end())
    {
        children.erase(itr);
        return true;
    }

    return false;
}

void FeatherContainer::Transform(const int x, const int y)
{
    std::shared_ptr<FeatherComponent> pParent = parent.lock();

    this->vPosition.x += x;
    this->vPosition.y += y;
    this->vPosition.x = std::clamp(static_cast<int>(vPosition.x), 0, pParent->width);
    this->vPosition.y = std::clamp(static_cast<int>(vPosition.y), 0, pParent->height);

    this->width = pParent->width - vPosition.x;
    this->height = pParent->height - vPosition.y;
}

void FeatherContainer::FixPosition(const int x, const int y)
{
    this->tPosition.x = x + vPosition.x;
    this->tPosition.y = y + vPosition.y;

    for (std::unique_ptr<FeatherComponent>& child : children)
    {
        child->FixPosition(this->tPosition.x, this->tPosition.y);
    }
}

void FeatherContainer::HandleInput(FeatherTouch* touch)
{
    for (std::unique_ptr<FeatherComponent>& childComponent : children)
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

    for (std::unique_ptr<FeatherComponent>& child : children)
    {
        if (child->render)
        {
            if (this->parent.lock() != nullptr)
            {
                RECT clampedScissor;

                clampedScissor = {
                    std::clamp(child->tPosition.x, rect.left, rect.right),
                    std::clamp(child->tPosition.y, rect.top, rect.bottom),
                    std::clamp(child->tPosition.x + child->width, rect.left, rect.right),
                    std::clamp(child->tPosition.y + child->height, rect.top, rect.bottom)
                };

                g_render.pDevice->SetScissorRect(&clampedScissor);
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
    std::shared_ptr<FeatherComponent> pParent = parent.lock();

    this->width = pParent->width;
    this->height = pParent->height;
}

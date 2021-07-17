#include <algorithm>
#include <concurrent_queue.h>
#include <mutex>
#include <Window/Window.h>

#include <DisplayInterface/Components/FeatherContainer.h>
#include <DisplayInterface/Components/FeatherButton.h>
#include <DisplayInterface/Components/FeatherLabel.h>
#include <DisplayInterface/Components/FeatherTabView.h>
#include <DisplayInterface/Components/FeatherButton.h>
#include <DisplayInterface/Components/FeatherTextBox.h>

FeatherContainer::FeatherContainer()
{ }

FeatherContainer::FeatherContainer(const std::shared_ptr<FeatherComponent> parent)
{
    this->parent = std::weak_ptr(parent);
    SetInitialProperties();
}

FeatherContainer::FeatherContainer(const std::shared_ptr<FeatherComponent> parent, FeatherComponent* child)
{
    this->parent = std::weak_ptr(parent);
    SetInitialProperties();

    AddControl<FeatherComponent>(std::shared_ptr<FeatherComponent>(child));
}

FeatherContainer::FeatherContainer(const std::shared_ptr<FeatherComponent> parent, FeatherComponent* child1, FeatherComponent* child2)
{
    this->parent = std::weak_ptr(parent);
    SetInitialProperties();

    AddControl<FeatherComponent>(std::shared_ptr<FeatherComponent>(child1));
    AddControl<FeatherComponent>(std::shared_ptr<FeatherComponent>(child2));
}

FeatherContainer::FeatherContainer(const std::shared_ptr<FeatherComponent> parent, FeatherComponent* child1, FeatherComponent* child2, FeatherComponent* child3)
{
    this->parent = std::weak_ptr(parent);
    SetInitialProperties();

    AddControl<FeatherComponent>(std::shared_ptr<FeatherComponent>(child1));
    AddControl<FeatherComponent>(std::shared_ptr<FeatherComponent>(child2));
    AddControl<FeatherComponent>(std::shared_ptr<FeatherComponent>(child3));
}



bool FeatherContainer::RemoveControl(const std::shared_ptr<FeatherComponent> component)
{
    window->postRenderQueue.enqueue([=, this] {
        for (auto child : children)
        {
            if (child == component)
            {
                children.erase(std::ranges::remove(children, child).begin(), children.end());
            }
        }
    });

    return false;
}

void FeatherContainer::Transform(const int x, const int y)
{
    std::shared_ptr<FeatherComponent> pParent = parent.lock();

    this->vPosition.x += x;
    this->vPosition.y += y;
    this->vPosition.x = std::clamp(static_cast<int>(vPosition.x), 0, pParent->GetWidth());
    this->vPosition.y = std::clamp(static_cast<int>(vPosition.y), 0, pParent->GetHeight());

    this->width = pParent->GetWidth() - vPosition.x;
    this->height = pParent->GetHeight() - vPosition.y;
}

void FeatherContainer::FixPosition(const int x, const int y)
{
    this->tPosition.x = x + vPosition.x;
    this->tPosition.y = y + vPosition.y;

    for (auto child : children)
    {
        child->FixPosition(this->tPosition.x, this->tPosition.y);
    }
}

void FeatherContainer::HandleInput(FeatherTouch* touch)
{
    for (std::shared_ptr<FeatherComponent> childComponent : children)
    {
        if (childComponent->GetRenderState())
        {
            if (touch->MouseInRegion(childComponent->GetTrueX(), childComponent->GetTrueY(), childComponent->GetWidth(), childComponent->GetHeight()))
            {
                if (!childComponent->MouseInRegion())
                {
                    childComponent->SetMouseInRegion(true);
                    childComponent->OnEnter(touch);
                }

                if (touch->KeyPressed(VK_LBUTTON))
                {
                    childComponent->SetHandlingMouseDownEvent(true);
                    childComponent->OnMousePressed(touch);
                }
                if (touch->KeyDown(VK_LBUTTON))
                {
                    childComponent->SetHandlingMouseDownEvent(true);
                    childComponent->OnMouseDown(touch);
                }
                else if (touch->KeyReleased(VK_LBUTTON))
                {
                    childComponent->SetHandlingMouseDownEvent(false);
                    childComponent->OnMouseUp(touch);
                }

                childComponent->OnHover(touch);
            }
            else if (childComponent->MouseInRegion())
            {
                childComponent->SetMouseInRegion(false);
                childComponent->OnLeave(touch);
            }
            else if (touch->KeyPressed(VK_LBUTTON))
            {
                childComponent->OnMouseClickAway(touch);
            }

            if (childComponent->HandlingMouseDownEvent())
            {
                if (touch->KeyReleased(VK_LBUTTON))
                {
                    childComponent->SetHandlingMouseDownEvent(false);
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

    for (auto child : children)
    {
        if (child->GetRenderState())
        {
            if (this->parent.lock() != nullptr)
            {
                RECT clampedScissor;

                clampedScissor = {
                    std::clamp(static_cast<long>(child->GetTrueX()), rect.left, rect.right),
                    std::clamp(static_cast<long>(child->GetTrueY()), rect.top, rect.bottom),
                    std::clamp(static_cast<long>(child->GetTrueX()) + child->GetWidth(), rect.left, rect.right),
                    std::clamp(static_cast<long>(child->GetTrueY()) + child->GetHeight(), rect.top, rect.bottom)
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

void FeatherContainer::SetComponentWindow(Window* window)
{
    FeatherComponent::SetComponentWindow(window);
    for (auto child : children)
    {
        child->SetComponentWindow(window);
    }
}

void FeatherContainer::SetInitialProperties()
{
    const std::shared_ptr<FeatherComponent> pParent = parent.lock();

    this->width = pParent->GetWidth();
    this->height = pParent->GetHeight();
}

void FeatherContainer::PushToQueue(std::function<void()> func)
{
    window->postRenderQueue.enqueue(func);
}

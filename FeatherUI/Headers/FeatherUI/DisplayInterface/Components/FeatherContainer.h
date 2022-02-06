#pragma once
#include <functional>
#include <memory>
#include <DisplayInterface/FeatherForwards.h>
#include <DisplayInterface/FeatherComponent.h>
#include <vector>

class FeatherContainer;

class FeatherContainer : public FeatherComponent
{
public:
    FeatherContainer();
    FeatherContainer(std::shared_ptr<FeatherComponent> parent);
    FeatherContainer(std::shared_ptr<FeatherComponent> parent, FeatherComponent* child);
    FeatherContainer(std::shared_ptr<FeatherComponent> parent, FeatherComponent* child1, FeatherComponent* child2);
    FeatherContainer(std::shared_ptr<FeatherComponent> parent, FeatherComponent* child1, FeatherComponent* child2, FeatherComponent* child3);

    std::vector<std::shared_ptr<FeatherComponent>> children;

    template <class T>
    std::shared_ptr<T> AddControl(std::shared_ptr<FeatherComponent> component)
    {
        if (window == nullptr)
        {
            component->SetParent(shared);
            component->SetComponentWindow(window);
            this->children.push_back(std::shared_ptr<FeatherComponent>(component));
        }
        else
        {
            PushToQueue([=, this]{
                component->SetParent(shared);
                this->children.push_back(std::shared_ptr<FeatherComponent>(component));
            });
        }

        return std::dynamic_pointer_cast<T>(component);
    }
    bool RemoveControl(std::shared_ptr<FeatherComponent> component);
    
    void Transform(int x, int y);
    void FixPosition(int x, int y) override;
    void HandleInput(FeatherTouch* touch) override;
    void Render() override;
    void SetComponentWindow(Window* window) override;

private:
    void SetInitialProperties();
    void PushToQueue(std::function<void()> func);
};

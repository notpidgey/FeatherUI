#pragma once

#include <DisplayInterface/FeatherForwards.h>
#include <DisplayInterface/FeatherComponent.h>
#include <vector>

class FeatherContainer : public FeatherComponent
{
public:
    FeatherComponent* parent;

    FeatherContainer()
    {
        this->parent = nullptr;
    }
    explicit FeatherContainer(FeatherComponent* parent)
    {
        this->parent = parent;
    }
    FeatherContainer(FeatherComponent* parent, FeatherComponent* child)
    {
        this->parent = parent;
        
        child->parent = parent;
        
        children.push_back(child);
    }
    FeatherContainer(FeatherComponent* parent, FeatherComponent* child1, FeatherComponent* child2)
    {
        this->parent = parent;
        
        child1->parent = child1;
        child2->parent = child2;
        
        children.push_back(child1);
        children.push_back(child2);
    }

    std::vector<FeatherComponent*> children;

    FeatherComponent* AddControl(FeatherComponent* component);
    void HandleInput(FeatherTouch* touch) const override;
    void Render() override;
};

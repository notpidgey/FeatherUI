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
        
        AddControl(child);
    }
    
    FeatherContainer(FeatherComponent* parent, FeatherComponent* child1, FeatherComponent* child2)
    {
        this->parent = parent;

        AddControl(child1);
        AddControl(child2);
    }

    FeatherContainer(FeatherComponent* parent, FeatherComponent* child1, FeatherComponent* child2, FeatherComponent* child3)
    {
        this->parent = parent;

        AddControl(child1);
        AddControl(child2);
        AddControl(child3);
    }


    std::vector<FeatherComponent*> children;

    FeatherComponent* AddControl(FeatherComponent* component);
    void HandleInput(FeatherTouch* touch) override;
    void Render() override;
};

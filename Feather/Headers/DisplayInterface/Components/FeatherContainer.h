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
        SetInitialProperties();
    }  
    FeatherContainer(FeatherComponent* parent, FeatherComponent* child)
    {
        this->parent = parent;
        SetInitialProperties();
        
        AddControl(child);
    }
    FeatherContainer(FeatherComponent* parent, FeatherComponent* child1, FeatherComponent* child2)
    {
        this->parent = parent;
        SetInitialProperties();

        AddControl(child1);
        AddControl(child2);
    }
    FeatherContainer(FeatherComponent* parent, FeatherComponent* child1, FeatherComponent* child2, FeatherComponent* child3)
    {
        this->parent = parent;
        SetInitialProperties();

        AddControl(child1);
        AddControl(child2);
        AddControl(child3);
    }

    std::vector<FeatherComponent*> children;

    FeatherComponent* AddControl(FeatherComponent* component);
    void ClampRect(FeatherComponent* child, RECT* currentScissor) const;
    void Transform(int x, int y);
    void FixPosition(int x, int y) override;
    void HandleInput(FeatherTouch* touch) override;
    void Render() override;

private:
    void SetInitialProperties();
};

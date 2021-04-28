#pragma once
#include <memory>
#include <DisplayInterface/FeatherForwards.h>
#include <DisplayInterface/FeatherComponent.h>
#include <vector>

class FeatherContainer : public FeatherComponent
{
public:
    FeatherContainer();
    FeatherContainer(std::shared_ptr<FeatherComponent> parent);
    FeatherContainer(std::shared_ptr<FeatherComponent> parent, FeatherComponent* child);
    FeatherContainer(std::shared_ptr<FeatherComponent> parent, FeatherComponent* child1, FeatherComponent* child2);
    FeatherContainer(std::shared_ptr<FeatherComponent> parent, FeatherComponent* child1, FeatherComponent* child2, FeatherComponent* child3);

    std::vector<std::unique_ptr<FeatherComponent>> children;

    FeatherComponent* AddControl(FeatherComponent* component);
    bool RemoveControl(FeatherComponent* component);
    
    void Transform(int x, int y);
    void FixPosition(int x, int y) override;
    void HandleInput(FeatherTouch* touch) override;
    void Render() override;

private:
    void SetInitialProperties();
};

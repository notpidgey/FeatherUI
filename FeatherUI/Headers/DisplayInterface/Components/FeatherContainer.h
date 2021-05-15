#pragma once
#include <memory>
#include <DisplayInterface/FeatherForwards.h>
#include <DisplayInterface/FeatherComponent.h>
#include <vector>

class FeatherContainer : public FeatherComponent
{
public:
    FeatherContainer();
    explicit FeatherContainer(std::shared_ptr<FeatherComponent> parent);
    FeatherContainer(std::shared_ptr<FeatherComponent> parent, FeatherComponent* child);
    FeatherContainer(std::shared_ptr<FeatherComponent> parent, FeatherComponent* child1, FeatherComponent* child2);
    FeatherContainer(std::shared_ptr<FeatherComponent> parent, FeatherComponent* child1, FeatherComponent* child2, FeatherComponent* child3);

    std::vector<std::shared_ptr<FeatherComponent>> children;

    std::shared_ptr<FeatherComponent> AddControl(std::shared_ptr<FeatherComponent> component);
    bool RemoveControl(std::shared_ptr<FeatherComponent> component);
    
    void Transform(int x, int y);
    void FixPosition(int x, int y) override;
    void HandleInput(FeatherTouch* touch) override;
    void Render() override;
    void SetComponentWindow(Window* window) override;

private:
    void SetInitialProperties();
};

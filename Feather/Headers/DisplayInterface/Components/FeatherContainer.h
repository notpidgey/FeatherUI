#pragma once

#include <DisplayInterface/FeatherForwards.h>
#include <DisplayInterface/FeatherComponent.h>
#include <vector>

class FeatherContainer : public FeatherComponent
{
public:
    std::vector<FeatherComponent*> children;

    FeatherComponent* AddControl(FeatherComponent* control);

    void HandleInput(FeatherTouch* touch) const override;
    void Render() override;
};
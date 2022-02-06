#pragma once
#include <FeatherUI/DisplayInterface/FeatherComponent.h>
#include <FeatherUI/DisplayInterface/Components/FeatherButton.h>
#include <FeatherUI/DisplayInterface/Components/FeatherContainer.h>

struct FeatherTabViewTab
{
    int tabId;
    FeatherButton* button;
    FeatherContainer* view;
};

class FeatherTabView : public FeatherComponent
{
public:
    FeatherTabView(int x, int y, int width, int height, int buttonHeight, ID3DXFont* font, std::vector<std::string> tabNames);

    void SetActiveTab(int tabIndex);
    bool AddToTab(std::shared_ptr<FeatherComponent> component, const int tabIndex);

private:
    std::shared_ptr<FeatherContainer> tabButtonContainer;
    std::shared_ptr<FeatherContainer> viewContainer;
    
    std::vector<FeatherTabViewTab> tabs;
    
    void OnTabButtonClick(FeatherButton* button);
};

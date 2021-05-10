#include <DisplayInterface/Components/FeatherTabView.h>
#include <DisplayInterface/Components/FeatherContainer.h>
#include <DisplayInterface/Components/FeatherButton.h>
#include <functional>

FeatherTabView::FeatherTabView(const int x, const int y, const int width, const int height, const int buttonHeight, ID3DXFont* font, std::vector<std::string> tabNames)
{
    FeatherComponent::SetPosition(x, y);
    this->width = width;
    this->height = height;
    this->childrenContainer = std::make_unique<FeatherContainer>(shared);

    auto tabContainer = std::dynamic_pointer_cast<FeatherContainer>(this->childrenContainer->AddControl(
        std::make_shared<FeatherContainer>(std::shared_ptr<FeatherComponent>(childrenContainer.get())
    )));
    tabContainer->SetHeight(buttonHeight);
    tabContainer->SetWidth(width);

    auto viewContainer = std::dynamic_pointer_cast<FeatherContainer>(this->childrenContainer->AddControl(
        std::make_shared<FeatherContainer>(std::shared_ptr<FeatherComponent>(childrenContainer.get())
    )));
    viewContainer->Transform(0, buttonHeight + 1);
    viewContainer->SetHeight(height - buttonHeight);
    viewContainer->SetWidth(width);

    int i = 0;
    const int sizePerButton = width / tabNames.size();
    for (auto tabName : tabNames)
    {
        FeatherTabViewTab newTab{};
        newTab.tabId = i;

        newTab.button = std::dynamic_pointer_cast<FeatherButton>(tabContainer->AddControl(
            std::make_shared<FeatherButton>(i * sizePerButton, 0, sizePerButton, buttonHeight, std::bind(&FeatherTabView::OnTabButtonClick, this, std::placeholders::_1), font, tabName)
        )).get();

        newTab.view = std::dynamic_pointer_cast<FeatherContainer>(viewContainer->AddControl(
                std::make_shared<FeatherContainer>(std::shared_ptr<FeatherComponent>(this)))
        ).get();
        newTab.view->SetRenderState(false);

        //newTab.view->backgroundColor = COLOR(255,255,255,255);

        i++;
        tabs.push_back(newTab);
    }
}

void FeatherTabView::SetActiveTab(const int tabIndex)
{
    for (FeatherTabViewTab tab : tabs)
    {
        if (tab.tabId != tabIndex)
            tab.view->SetRenderState(false);
        else
            tab.view->SetRenderState(true);
    }
}

bool FeatherTabView::AddToTab(FeatherComponent* component, const int tabIndex)
{
    for (FeatherTabViewTab tab : tabs)
    {
        if (tab.tabId == tabIndex)
        {
            tab.view->AddControl(std::shared_ptr<FeatherComponent>(component));
            return true;
        }
    }

    return false;
}

void FeatherTabView::OnTabButtonClick(FeatherButton* button)
{
    for (FeatherTabViewTab tab : tabs)
    {
        if (tab.button == button)
        {
            SetActiveTab(tab.tabId);
        }
    }
}

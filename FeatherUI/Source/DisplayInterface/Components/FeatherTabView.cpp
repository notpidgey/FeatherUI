#include <DisplayInterface/Components/FeatherTabView.h>
#include <DisplayInterface/Components/FeatherContainer.h>
#include <DisplayInterface/Components/FeatherButton.h>
#include <functional>

FeatherTabView::FeatherTabView(const int x, const int y, const int width, const int height, const int buttonHeight, ID3DXFont* font, std::vector<const char*> tabNames)
{
    FeatherComponent::SetPosition(x, y);
    this->width = width;
    this->height = height;
    this->childrenContainer = new FeatherContainer(this);

    FeatherContainer* tabContainer = (FeatherContainer*)this->childrenContainer->AddControl(new FeatherContainer(childrenContainer));
    tabContainer->height = buttonHeight;
    tabContainer->width = width;

    FeatherContainer* viewContainer = (FeatherContainer*)this->childrenContainer->AddControl(new FeatherContainer(childrenContainer));
    viewContainer->Transform(0, buttonHeight + 1);
    viewContainer->height = height - buttonHeight;
    viewContainer->width = width;


    int i = 0;
    const int sizePerButton = width / tabNames.size();
    for (const char* tabName : tabNames)
    {
        FeatherTabViewTab newTab{};
        newTab.tabId = i;

        newTab.button = static_cast<FeatherButton*>(tabContainer->AddControl(
            new FeatherButton(i * sizePerButton, 0, sizePerButton, buttonHeight, std::bind(&FeatherTabView::OnTabButtonClick, this, std::placeholders::_1), font, tabName)
        ));
        
        newTab.view = static_cast<FeatherContainer*>(viewContainer->AddControl(
                new FeatherContainer(this))
        );
        newTab.view->render = false;

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
            tab.view->render = false;
        else
            tab.view->render = true;
    }
}

bool FeatherTabView::AddToTab(FeatherComponent* component, const int tabIndex)
{
    for (FeatherTabViewTab tab : tabs)
    {
        if (tab.tabId == tabIndex)
        {
            tab.view->AddControl(component);
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

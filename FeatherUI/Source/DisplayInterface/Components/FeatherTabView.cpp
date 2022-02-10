#include <FeatherUI/DisplayInterface/Components/FeatherTabView.h>
#include <FeatherUI/DisplayInterface/Components/FeatherContainer.h>
#include <FeatherUI/DisplayInterface/Components/FeatherButton.h>
#include <functional>

FeatherTabView::FeatherTabView(const int x, const int y, const int width, const int height, const int buttonHeight,
	ID3DXFont* font, std::vector<std::string> tabNames)
{
	FeatherComponent::SetPosition(x, y);
	this->width = width;
	this->height = height;

	tabButtonContainer = std::make_shared<FeatherContainer>();
	tabButtonContainer->SetHeight(buttonHeight);
	tabButtonContainer->SetWidth(width);

	viewContainer = std::make_shared<FeatherContainer>();
	viewContainer->SetHeight(height - buttonHeight);
	viewContainer->SetWidth(width);

	this->childrenContainer = std::make_unique<FeatherContainer>(shared, tabButtonContainer.get(), viewContainer.get());
	viewContainer->Transform(0, buttonHeight + 1);

	const int sizePerButton = width / tabNames.size();
	for (int i = 0; std::string& tabName: tabNames)
	{
		FeatherTabViewTab newTab{};
		newTab.tabId = i;

		newTab.button = tabButtonContainer->AddControl<FeatherButton>(
			std::make_shared<FeatherButton>(i * sizePerButton, 0, sizePerButton, buttonHeight,
				std::bind(&FeatherTabView::OnTabButtonClick, this, std::placeholders::_1), font, tabName)
		).get();

		newTab.view = viewContainer->AddControl<FeatherContainer>(
			std::make_shared<FeatherContainer>(viewContainer)
		).get();
		newTab.view->SetRenderState(false);

		i++;
		tabs.push_back(newTab);
	}
}

FeatherTabView::FeatherTabView(int x, int y, int width, int height, int buttonHeight, ID3DXFont* font,
	std::vector<std::wstring> tabNames)
{
	FeatherComponent::SetPosition(x, y);
	this->width = width;
	this->height = height;

	tabButtonContainer = std::make_shared<FeatherContainer>();
	tabButtonContainer->SetHeight(buttonHeight);
	tabButtonContainer->SetWidth(width);

	viewContainer = std::make_shared<FeatherContainer>();
	viewContainer->SetHeight(height - buttonHeight);
	viewContainer->SetWidth(width);

	this->childrenContainer = std::make_unique<FeatherContainer>(shared, tabButtonContainer.get(), viewContainer.get());
	viewContainer->Transform(0, buttonHeight + 1);

	const int sizePerButton = width / tabNames.size();
	for (int i = 0; std::wstring& tabName: tabNames)
	{
		FeatherTabViewTab newTab{};
		newTab.tabId = i;

		newTab.button = tabButtonContainer->AddControl<FeatherButton>(
			std::make_shared<FeatherButton>(i * sizePerButton, 0, sizePerButton, buttonHeight,
				std::bind(&FeatherTabView::OnTabButtonClick, this, std::placeholders::_1), font, tabName)
		).get();

		newTab.view = viewContainer->AddControl<FeatherContainer>(
			std::make_shared<FeatherContainer>(viewContainer)
		).get();
		newTab.view->SetRenderState(false);

		i++;
		tabs.push_back(newTab);
	}
}

void FeatherTabView::SetActiveTab(const int tabIndex)
{
	for (FeatherTabViewTab tab: tabs)
	{
		if (tab.tabId != tabIndex)
			tab.view->SetRenderState(false);
		else
			tab.view->SetRenderState(true);
	}
}

bool FeatherTabView::AddToTab(const std::shared_ptr<FeatherComponent> component, const int tabIndex)
{
	for (auto[tabId, button, view]: tabs)
	{
		if (tabId == tabIndex)
		{
			view->AddControl<FeatherComponent>(std::shared_ptr<FeatherComponent>(component));
			return true;
		}
	}

	return false;
}

void FeatherTabView::OnTabButtonClick(FeatherButton* button)
{
	for (FeatherTabViewTab tab: tabs)
	{
		if (tab.button == button)
		{
			SetActiveTab(tab.tabId);
		}
	}
}

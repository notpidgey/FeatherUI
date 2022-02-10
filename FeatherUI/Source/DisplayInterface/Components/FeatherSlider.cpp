#include <FeatherUI/DisplayInterface/Components/FeatherSlider.h>
#include <FeatherUI/DisplayInterface/Components/FeatherLabel.h>
#include <FeatherUI/DisplayInterface/Components/FeatherContainer.h>
#include <FeatherUI/Graphics/DirectX9/RenderEngine.h>
#include <algorithm>
#include <sstream>
#include <iomanip>

FeatherSlider::FeatherSlider(const int x, const int y, const int width, const short decimalPlaces, const float min,
	const float max, std::atomic<float>* out,
	ID3DXFont* font, const std::string& labelText)
{
	FeatherComponent::SetPosition(x, y);

	this->decimalPlaces = decimalPlaces;
	this->minValue = min;
	this->maxValue = max;
	this->sliderValue = out;

	sliderTextValueless = labelText;
	this->sliderLabel = std::make_shared<FeatherLabel>(0, 0, font, labelText, COLOR(255, 0, 0, 0));
	this->sliderKnob = std::make_shared<FeatherSliderKnob>(HORIZONTAL_PADDING, TEXT_SLIDER_PADDING + VERTICAL_PADDING,
		width - (HORIZONTAL_PADDING * 2),
		BACKGROUND_HEIGHT - (VERTICAL_PADDING * 2));

	this->width = width;
	this->height =
		sliderLabel->GetTextHeight() + (TEXT_SLIDER_PADDING - sliderLabel->GetTextHeight()) + BACKGROUND_HEIGHT;

	this->childrenContainer = std::make_unique<FeatherContainer>(
		shared,
		sliderLabel.get(),
		sliderKnob.get()
	);

	sliderKnob->knobPercentage = ((sliderValue->load() - min)) / (max - min);
}

FeatherSlider::FeatherSlider(const int x, const int y, const int width, const short decimalPlaces, const float min,
	const float max, std::atomic<float>* out,
	ID3DXFont* font, const std::wstring& labelText)
{
	FeatherComponent::SetPosition(x, y);

	this->decimalPlaces = decimalPlaces;
	this->minValue = min;
	this->maxValue = max;
	this->sliderValue = out;

	sliderTextValuelessW = labelText;
	this->sliderLabel = std::make_shared<FeatherLabel>(0, 0, font, labelText, COLOR(255, 0, 0, 0));
	this->sliderKnob = std::make_shared<FeatherSliderKnob>(HORIZONTAL_PADDING, TEXT_SLIDER_PADDING + VERTICAL_PADDING,
		width - (HORIZONTAL_PADDING * 2),
		BACKGROUND_HEIGHT - (VERTICAL_PADDING * 2));

	this->width = width;
	this->height =
		sliderLabel->GetTextHeight() + (TEXT_SLIDER_PADDING - sliderLabel->GetTextHeight()) + BACKGROUND_HEIGHT;

	this->childrenContainer = std::make_unique<FeatherContainer>(
		shared,
		sliderLabel.get(),
		sliderKnob.get()
	);

	sliderKnob->knobPercentage = ((sliderValue->load() - min)) / (max - min);
}

float FeatherSlider::GetValue() const
{
	return minValue + (sliderKnob->knobPercentage * (maxValue - minValue));
}

std::string FeatherSlider::FloatToString(const float number) const
{
	std::stringstream stream;
	stream << std::fixed << std::setprecision(decimalPlaces) << number;

	return stream.str();
}

std::wstring FeatherSlider::FloatToStringW(const float number) const
{
	std::wstringstream stream;
	stream << std::fixed << std::setprecision(decimalPlaces) << number;

	return stream.str();
}

void FeatherSlider::Render()
{
	//Slider background
	g_render.RectFilled1(tPosition.x, tPosition.y + TEXT_SLIDER_PADDING, width, BACKGROUND_HEIGHT,
		COLOR(255, 33, 33, 33));

	sliderValue->store(GetValue());
	if (sliderTextValueless)
		sliderLabel->SetLabelText(sliderTextValueless.value() + " - " + FloatToString(sliderValue->load()));
	else
		sliderLabel->SetLabelText(sliderTextValuelessW.value() + L" - " + FloatToStringW(sliderValue->load()));
	sliderLabel->ResetTextWidth();

	FeatherComponent::Render();
}

FeatherSliderKnob::FeatherSliderKnob(const int x, const int y, const int width, const int height)
{
	FeatherComponent::SetPosition(x, y);
	this->width = width;
	this->height = height;
	this->knobPercentage = 0;
}

float FeatherSliderKnob::GetRenderOffset() const
{
	return knobPercentage * (width - KNOB_WIDTH);
}

void FeatherSliderKnob::Render()
{
	g_render.RectFilled1(tPosition.x + GetRenderOffset(), tPosition.y, KNOB_WIDTH, KNOB_HEIGHT,
		COLOR(255, 255, 255, 255));
}

void FeatherSliderKnob::OnMouseUp(FeatherTouch* touch)
{
	beingDragged = false;
}

void FeatherSliderKnob::OnMousePressed(FeatherTouch* touch)
{
	if (touch->MouseInRegion(tPosition.x + GetRenderOffset(), tPosition.y, KNOB_WIDTH, KNOB_HEIGHT))
	{
		beingDragged = true;
		dragAnchor.x = ((tPosition.x + GetRenderOffset()) - touch->mousePos.x);
	}
}

void FeatherSliderKnob::OnMouseDown(FeatherTouch* touch)
{
	//If is inside the knob region
	if (touch->MouseInRegion(tPosition.x + GetRenderOffset(), tPosition.y, KNOB_WIDTH, KNOB_HEIGHT))
	{
		knobPercentage = static_cast<float>(std::clamp(touch->mousePos.x + dragAnchor.x, tPosition.x,
			tPosition.x + width - KNOB_WIDTH) - tPosition.x) / (width - KNOB_WIDTH);
	}
}

void FeatherSliderKnob::OnMouseAway(FeatherTouch* touch)
{
	if (touch->KeyDown(VK_LBUTTON) && beingDragged)
	{
		knobPercentage = static_cast<float>(std::clamp(touch->mousePos.x + dragAnchor.x, tPosition.x,
			tPosition.x + width - KNOB_WIDTH) - tPosition.x) / (width - KNOB_WIDTH);
	}
}

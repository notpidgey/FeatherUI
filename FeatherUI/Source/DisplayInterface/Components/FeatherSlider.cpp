#include <DisplayInterface/Components/FeatherSlider.h>
#include <DisplayInterface/Components/FeatherLabel.h>
#include <DisplayInterface/Components/FeatherContainer.h>
#include <Graphics/DirectX9/RenderEngine.h>
#include <algorithm>
#include <sstream>
#include <iomanip>


FeatherSlider::FeatherSlider(const int x, const int y, const int width, const SLIDER_UNIT unit, const float min, const float max, float* out, ID3DXFont* font, const std::string& labelText)
{
    FeatherComponent::SetPosition(x, y);
    this->unit = unit;
    this->minValue = min;
    this->maxValue = max;
    this->sliderValue = out;

    this->sliderLabel = std::make_shared<FeatherLabel>(0, 0, font, labelText, COLOR(255, 0, 0, 0));
    this->sliderValueLabel = std::make_shared<FeatherLabel>(0, 0, font, sliderValueText, COLOR(255, 0, 0, 0));
    this->sliderKnob = std::make_shared<FeatherSliderKnob>(HORIZONTAL_PADDING, TEXT_SLIDER_PADDING + VERTICAL_PADDING, width - (HORIZONTAL_PADDING * 2),
        BACKGROUND_HEIGHT - (VERTICAL_PADDING * 2));

    this->width = width;
    this->height = sliderLabel->GetTextHeight() + (TEXT_SLIDER_PADDING - sliderLabel->GetTextHeight()) + BACKGROUND_HEIGHT;

    this->childrenContainer = std::make_unique<FeatherContainer>(
        shared,
        sliderLabel.get(),
        sliderValueLabel.get(),
        sliderKnob.get()
    );
}

float FeatherSlider::GetValue() const
{
    const float curr = minValue + (sliderKnob->knobPercentage * (maxValue - minValue));
    *sliderValue = curr;
    
    return curr;
}

std::string FeatherSlider::FloatToString(const float number, int precision = 2)
{
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << number;
    return stream.str();
}

void FeatherSlider::Render()
{
    //Slider background
    g_render.RectFilled1(tPosition.x, tPosition.y + TEXT_SLIDER_PADDING, width, BACKGROUND_HEIGHT, COLOR(255, 33, 33, 33));

    sliderValueText.erase();
    switch (unit)
    {
    case NONE:
        sliderValueText = FloatToString(GetValue());
        break;
    case PERCENTAGE:
        sliderValueText = FloatToString(sliderKnob->knobPercentage * 100);
        sliderValueText.append(" %");
        break;
    case FEET:
        sliderValueText = FloatToString(GetValue());
        sliderValueText.append(" FT");
        break;
    case METERS:
        sliderValueText = FloatToString(GetValue());
        sliderValueText.append(" M");
        break;
    case MILLIMETERS:
        sliderValueText = FloatToString(GetValue());
        sliderValueText.append(" MM");
        break;
    }

    sliderValueLabel->SetX(width - sliderValueLabel->GetTextWidth());

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
    g_render.RectFilled1(tPosition.x + GetRenderOffset(), tPosition.y, KNOB_WIDTH, KNOB_HEIGHT, COLOR(255, 255, 255, 255));
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
        knobPercentage = static_cast<float>(std::clamp(touch->mousePos.x + dragAnchor.x, tPosition.x, tPosition.x + width - KNOB_WIDTH) - tPosition.x) / (width - KNOB_WIDTH);
    }
}

void FeatherSliderKnob::OnMouseAway(FeatherTouch* touch)
{
    if (touch->KeyDown(VK_LBUTTON) && beingDragged)
    {
        knobPercentage = static_cast<float>(std::clamp(touch->mousePos.x + dragAnchor.x, tPosition.x, tPosition.x + width - KNOB_WIDTH) - tPosition.x) / (width - KNOB_WIDTH);
    }
}

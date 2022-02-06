#pragma once
#include <DisplayInterface/FeatherComponent.h>
#include <DisplayInterface/Components/FeatherLabel.h>

#define TEXT_SLIDER_PADDING 15
#define BACKGROUND_HEIGHT 20
#define KNOB_HEIGHT 16
#define KNOB_WIDTH 16
#define HORIZONTAL_PADDING 2
#define VERTICAL_PADDING 2

class FeatherSliderKnob;

class FeatherSlider : public FeatherComponent
{
public:
    FeatherSlider(int x, int y, int width, short decimalPlaces, float min, float max, std::atomic<float>* out, ID3DXFont* font, const std::string& labelText);

    float GetValue() const;

private:
    short decimalPlaces;
    std::string sliderTextValueless;
    float maxValue;
    float minValue;
    std::atomic<float>* sliderValue;
    
    std::shared_ptr<FeatherLabel> sliderLabel;
    std::shared_ptr<FeatherSliderKnob> sliderKnob;

    std::string FloatToString(const float number) const;
    void Render() override;
};

class FeatherSliderKnob : public FeatherComponent
{
public:
    float knobPercentage;
    
    FeatherSliderKnob(int x, int y, int width, int height);
    
    void Render() override;
    void OnMouseUp(FeatherTouch* touch) override;
    void OnMousePressed(FeatherTouch* touch) override;
    void OnMouseDown(FeatherTouch* touch) override;
    void OnMouseAway(FeatherTouch* touch) override;

private:
    POINT dragAnchor;
    int hPadding;
    bool beingDragged;
    
    float GetRenderOffset() const;
};
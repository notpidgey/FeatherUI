#pragma once
#include <DisplayInterface/FeatherComponent.h>
#include <DisplayInterface/Components/FeatherLabel.h>

#define TEXT_SLIDER_PADDING 15
#define BACKGROUND_HEIGHT 20
#define KNOB_HEIGHT 16
#define KNOB_WIDTH 16
#define HORIZONTAL_PADDING 2
#define VERTICAL_PADDING 2

class FeatherSlider : public FeatherComponent
{
public:
    enum SLIDER_UNIT
    {
        PERCENTAGE,
        FEET,
        METERS,
        MILLIMETERS,
        NONE
    };

    FeatherLabel* sliderLabel;
    FeatherLabel* sliderValueLabel;
    
    SLIDER_UNIT unit;
    float maxValue;
    float minValue;
    
    FeatherSlider(int x, int y, int width, SLIDER_UNIT unit, float min, float max, ID3DXFont* font, const char* labelText);
    float GetValue() const;
    void Render() override;
    void OnMouseDown(FeatherTouch* touch) override;
};

class FeatherSliderKnob : public FeatherComponent
{
public:
    POINT dragAnchor;
    int hPadding;
    bool beingDragged;
    float knobPercentage;
    
    FeatherSliderKnob(int x, int y, int width, int height);
    
    void Render() override;
    void OnMouseUp(FeatherTouch* touch) override;
    void OnMousePressed(FeatherTouch* touch) override;
    void OnMouseDown(FeatherTouch* touch) override;
    void OnMouseAway(FeatherTouch* touch) override;

private:
    float GetRenderOffset() const;
};
/*
  ==============================================================================

    LookAndFeel.h
    Created: 24 Apr 2023 9:11:33pm
    Author:  thoma

  ==============================================================================
*/

#pragma once


#include "JuceHeader.h"

class OtherLookAndFeel : public juce::LookAndFeel_V4
{
public:
    OtherLookAndFeel();
    //! [otherLookAndFeel]

    //! [drawRotarySlider]
    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
        const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider) override;

    void drawToggleButton(juce::Graphics& g,
        juce::ToggleButton& toggleButton,
        bool shouldDrawButtonAsHighlighted,
        bool shouldDrawButtonAsDown) override;
};
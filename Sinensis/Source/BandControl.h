/*
  ==============================================================================

    BandControl.h
    Created: 3 Apr 2023 9:15:51am
    Author:  thoma

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "LookAndFeel.h"

struct BandControl : juce::Component {

    BandControl(juce::AudioProcessorValueTreeState& apvts);

    void paint(juce::Graphics& g) override;
    void resized() override;

    juce::Colour back_ground_color;

private:

    OtherLookAndFeel otherLookAndFeel;

    juce::Slider BandSelectorSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>BandSelectorAttachement;
    juce::Label BandSelectorLabel;

    juce::Slider ratioSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>ratioAttachement;
    juce::Label ratioLabel;

    juce::TextButton lowHighButton{ "Low | High" };
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment>lowHighButtonAttachement;
    juce::TextButton oddEvenButton{ "Odd | Even" };
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment>oddEvenButtonAttachement;
    juce::TextButton peakButton{ "Peak" };
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment>peakButtonAttachement;

};
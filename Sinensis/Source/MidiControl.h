/*
  ==============================================================================

    MidiControl.h
    Created: 3 Apr 2023 9:16:17am
    Author:  thoma

  ==============================================================================
*/

#pragma once


#include "JuceHeader.h"
#include "LookAndFeel.h"

struct MidiControl : juce::Component {

    MidiControl(juce::AudioProcessorValueTreeState& apvts);

    void paint(juce::Graphics& g) override;

    void resized() override;

    juce::Colour back_ground_color;

private:

    OtherLookAndFeel otherLookAndFeel;

    juce::TextButton midiOffButton{ "Off" };
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment>midiOffButtonAttachement;
    juce::TextButton midiMonoButton{ "Mono" };
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment>midiMonoButtonAttachement;
    juce::TextButton midiPolyButton{ "Poly" };
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment>midiPolyButtonAttachement;

    juce::Slider cutoffFrequencySlider;
    juce::Slider attackSlider;
    juce::Slider decaySlider;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>cutoffFrequencyAttachement;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>attackAttachement;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>decayAttachement;


    juce::Label cutoffFrequencyLabel;
    juce::Label attackLabel;
    juce::Label decayLabel;
};
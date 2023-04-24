/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "LookAndFeel.h"

//==============================================================================
/**
*/
class WiltAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    WiltAudioProcessorEditor (WiltAudioProcessor&, juce::AudioProcessorValueTreeState&);
    ~WiltAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    WiltAudioProcessor& audioProcessor;

    OtherLookAndFeel otherLookAndFeel;

    juce::Slider feedbackSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>feedbackAttachement;
    juce::Label feedbackLabel;

    juce::Slider speedSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>speedAttachement;
    juce::Label speedLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WiltAudioProcessorEditor)
};

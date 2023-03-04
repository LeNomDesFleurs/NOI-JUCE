/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class SinensisAudioProcessorEditor  :   public juce::AudioProcessorEditor
{
public:
    SinensisAudioProcessorEditor(SinensisAudioProcessor&, juce::AudioProcessorValueTreeState& vts);
    //SinensisAudioProcessorEditor (SinensisAudioProcessor&);
    ~SinensisAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SinensisAudioProcessor& audioProcessor;

    juce::Slider cutoffFrequencySlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
        cutoffFrequencyAttachment;
    juce::Label cutoffFrequencyLabel;

    juce::Slider ratioSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
        ratioAttachment;
    juce::Label ratioLabel;

    juce::Slider QSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
        QAttachement;
    juce::Label QLabel;

    juce::Slider numberOfBandSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
        numberOfBandAttachement;
    juce::Label numberOfBandLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SinensisAudioProcessorEditor)
};

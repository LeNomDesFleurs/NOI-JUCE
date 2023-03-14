/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class OtherLookAndFeel : public juce::LookAndFeel_V4
{
public:
    OtherLookAndFeel()
    {
        setColour(juce::Slider::thumbColourId, juce::Colours::red);
    }
    //! [otherLookAndFeel]

    //! [drawRotarySlider]
    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
        const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider&) override
        //! [drawRotarySlider]
    {
        //! [locals]
        auto radius = (float)juce::jmin(width / 2, height / 2) - 10.0f;
        auto centreX = (float)x + (float)width * 0.5f;
        auto centreY = (float)y + (float)height * 0.5f;
        auto rx = centreX - radius;
        auto ry = centreY - radius;
        auto rw = radius * 2.0f;
        auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        //! [locals]

        //! [outline]
                // fill
        //g.setColour(juce::Colours::whitesmoke);
        //g.fillEllipse(rx, ry, rw, rw);

        // outline
        g.setColour(juce::Colours::black);
        g.drawEllipse(rx, ry, rw, rw, 15.0f);
        //! [outline]

        //! [path]
        juce::Path p;
        auto pointerLength = radius * 0.33f;
        auto pointerThickness = 7.0f;
  
        p.addEllipse(-pointerThickness * 0.5f + 2.0f, -radius, pointerThickness, pointerThickness);
        p.applyTransform(juce::AffineTransform::rotation(angle).translated(centreX, centreY));
        //! [path]

        //! [pointer]
                // pointer
        g.setColour(juce::Colours::white);
        g.fillPath(p);
        //! [pointer]
    }
};
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

    OtherLookAndFeel otherLookAndFeel; // [2]

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

    juce::Slider BandSelectorSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
        BandSelectorAttachement;
    juce::Label BandSelectorLabel;

    juce::ToggleButton midiButton;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment>midiAttachement;
    juce::Label midiLabel;

    juce::Slider BandSelectorModeSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
        BandSelectorModeAttachement;
    juce::Label BandSelectorModeLabel;

    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SinensisAudioProcessorEditor)
};



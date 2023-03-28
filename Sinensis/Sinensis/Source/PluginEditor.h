/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "MultipleChoice.h"

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
                                       const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider) override
        //! [drawRotarySlider]
    {
        //! [locals]
        auto outline = juce::Colours::black;
        auto fill = juce::Colours::lightgrey;

        auto bounds = juce::Rectangle<int>(x, y, width, height).toFloat().reduced(10);

        auto radius = juce::jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f;
        auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        auto lineW = juce::jmin(1.0f, radius * 0.5f);
        auto arcRadius = radius - lineW * 0.5f;

        juce::Path backgroundArc;
        backgroundArc.addCentredArc(bounds.getCentreX(),
            bounds.getCentreY(),
            arcRadius,
            arcRadius,
            0.0f,
            rotaryStartAngle,
            rotaryEndAngle,
            true);

        g.setColour(outline);
        g.strokePath(backgroundArc, juce::PathStrokeType(lineW, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));

        if (slider.isEnabled())
        {
            juce::Path valueArc;
            valueArc.addCentredArc(bounds.getCentreX(),
                bounds.getCentreY(),
                arcRadius,
                arcRadius,
                0.0f,
                rotaryStartAngle,
                toAngle,
                true);

            g.setColour(fill);
            g.strokePath(valueArc, juce::PathStrokeType(lineW, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
        }

        //auto thumbWidth = lineW * 2.0f;
        /*juce::Point<float> thumbPoint(bounds.getCentreX() + arcRadius * std::cos(toAngle - juce::MathConstants<float>::halfPi),
            bounds.getCentreY() + arcRadius * std::sin(toAngle - juce::MathConstants<float>::halfPi));*/

        g.setColour(slider.findColour(juce::Slider::thumbColourId));
       // g.fillEllipse(juce::Rectangle<float>(thumbWidth, thumbWidth).withCentre(thumbPoint));
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


    juce::TextButton midiOffButton{ "Off" };
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment>midiOffButtonAttachement;
    juce::TextButton midiMonoButton{ "Mono" };
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment>midiMonoButtonAttachement;
    juce::TextButton midiPolyButton{ "Poly" };
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment>midiPolyButtonAttachement;

    juce::ComboBox bandModeSelector;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment>bandModeAttachement;

    juce::ComboBox midiModeSelector;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment>midiModeAttachement;

    juce::Slider cutoffFrequencySlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>cutoffFrequencyAttachement;
    juce::Label cutoffFrequencyLabel;

    juce::Slider ratioSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>ratioAttachement;
    juce::Label ratioLabel;

    juce::Slider QSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>QAttachement;
    juce::Label QLabel;

    juce::Slider BandSelectorSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>BandSelectorAttachement;
    juce::Label BandSelectorLabel;

    juce::Slider outputVolumeSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>outputVolumeAttachement;
    juce::Label outputVolumeLabel;

    juce::Slider attackSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>attackAttachement;
    juce::Label attackLabel;

    juce::Slider decaySlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>decayAttachement;
    juce::Label decayLabel;

    //MultipleChoice MidiChoice;
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SinensisAudioProcessorEditor)
};



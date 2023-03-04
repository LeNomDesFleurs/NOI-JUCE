/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================

SinensisAudioProcessorEditor::SinensisAudioProcessorEditor(
    SinensisAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor(&p), audioProcessor(p) {
    const float text_box_width = 50.0f;
    //------------------------------------------------------
    addAndMakeVisible(cutoffFrequencySlider);
    cutoffFrequencySlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    cutoffFrequencyAttachment.reset(
        new juce::AudioProcessorValueTreeState::SliderAttachment
        (vts, "cutoff_frequency", cutoffFrequencySlider));
    cutoffFrequencySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, text_box_width, cutoffFrequencySlider.getTextBoxHeight());

    addAndMakeVisible(cutoffFrequencyLabel);
    cutoffFrequencyLabel.setText("Cutoff Frequency",
        juce::dontSendNotification);
    //-------------------------------------------------------
    addAndMakeVisible(ratioSlider);
    ratioSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    ratioAttachment.reset(
        new juce::AudioProcessorValueTreeState::SliderAttachment
        (vts, "ratio", ratioSlider));
    ratioSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, text_box_width, ratioSlider.getTextBoxHeight());


    addAndMakeVisible(ratioLabel);
    ratioLabel.setText("Ratio", juce::dontSendNotification);
    //-------------------------------------------------------
    addAndMakeVisible(QSlider);
    QSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    QAttachement.reset(
        new juce::AudioProcessorValueTreeState::SliderAttachment
        (vts, "Q", QSlider));
    QSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, text_box_width, QSlider.getTextBoxHeight());

    addAndMakeVisible(QLabel);
    QLabel.setText("Q", juce::dontSendNotification);
    //-------------------------------------------------------
    addAndMakeVisible(numberOfBandSlider);
    numberOfBandSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    numberOfBandAttachement.reset(
        new juce::AudioProcessorValueTreeState::SliderAttachment
        (vts, "number_of_band", numberOfBandSlider));
    numberOfBandSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, text_box_width, numberOfBandSlider.getTextBoxHeight());


    addAndMakeVisible(numberOfBandLabel);
    numberOfBandLabel.setText("Number Of Band", juce::dontSendNotification);

    setSize(400, 400);
}

SinensisAudioProcessorEditor::~SinensisAudioProcessorEditor()
{
}

//==============================================================================
void SinensisAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);

    g.drawFittedText("Sinensis", 0, 0, getWidth(), 30, juce::Justification::centred, 1);
}

void SinensisAudioProcessorEditor::resized()
{
    const int marge_haute_slider = 70;

    cutoffFrequencySlider.setBounds({ 25, marge_haute_slider, 100, 300 });
    cutoffFrequencyLabel.setBounds({ cutoffFrequencySlider.getX() - 20,
                                    cutoffFrequencySlider.getY() - 30,
                                    200, 50 });

    ratioSlider.setBounds({ 100, marge_haute_slider, 100, 300 });
    ratioLabel.setBounds({ ratioSlider.getX() + 30,
                                    ratioSlider.getY() - 30,
                                    200, 50 });

    QSlider.setBounds({ 175, marge_haute_slider, 100, 300 });
    QLabel.setBounds({ QSlider.getX() + 35,
                                    QSlider.getY() - 30,
                                    200, 50 });

    numberOfBandSlider.setBounds({ 250, marge_haute_slider, 100, 300 });
    numberOfBandLabel.setBounds({ numberOfBandSlider.getX(),
                                    numberOfBandSlider.getY() - 30,
                                    200, 50 });

    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

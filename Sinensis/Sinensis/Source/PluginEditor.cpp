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
    cutoffFrequencySlider.setLookAndFeel(&otherLookAndFeel);
    cutoffFrequencySlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    cutoffFrequencyAttachment.reset(
        new juce::AudioProcessorValueTreeState::SliderAttachment
        (vts, "cutoff_frequency", cutoffFrequencySlider));
    cutoffFrequencySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, text_box_width, cutoffFrequencySlider.getTextBoxHeight());

    addAndMakeVisible(cutoffFrequencyLabel);
    cutoffFrequencyLabel.setText("Cutoff Frequency",
        juce::dontSendNotification);
    //-------------------------------------------------------
    addAndMakeVisible(ratioSlider);
    ratioSlider.setLookAndFeel(&otherLookAndFeel);
    ratioSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    ratioAttachment.reset(
        new juce::AudioProcessorValueTreeState::SliderAttachment
        (vts, "ratio", ratioSlider));
    ratioSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, text_box_width, ratioSlider.getTextBoxHeight());


    addAndMakeVisible(ratioLabel);
    ratioLabel.setText("Ratio", juce::dontSendNotification);
    //-------------------------------------------------------
    addAndMakeVisible(QSlider);
    QSlider.setLookAndFeel(&otherLookAndFeel);
    QSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    QAttachement.reset(
        new juce::AudioProcessorValueTreeState::SliderAttachment
        (vts, "Q", QSlider));
    QSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, text_box_width, QSlider.getTextBoxHeight());

    addAndMakeVisible(QLabel);
    QLabel.setText("Q", juce::dontSendNotification);
    //-------------------------------------------------------
    addAndMakeVisible(numberOfBandSlider);
    numberOfBandSlider.setLookAndFeel(&otherLookAndFeel);
    numberOfBandSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    numberOfBandAttachement.reset(
        new juce::AudioProcessorValueTreeState::SliderAttachment
        (vts, "number_of_band", numberOfBandSlider));
    numberOfBandSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, text_box_width, numberOfBandSlider.getTextBoxHeight());


    addAndMakeVisible(numberOfBandLabel);
    numberOfBandLabel.setText("Number Of Band", juce::dontSendNotification);
    //--------------------------------------------------------
    addAndMakeVisible(bandModeButton);
    //bandModeButton.reset(new juce::AudioProcessorValueTreeState::ButtonAttachment(vts, "band_mode", bandModeButton));

    setSize(400, 300);
}

SinensisAudioProcessorEditor::~SinensisAudioProcessorEditor()
{
}

//==============================================================================
void SinensisAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
   // g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.fillAll(juce::Colours::darkgrey);
    g.setColour (juce::Colours::whitesmoke);
    g.setFont (15.0f);

    g.drawFittedText("Sinensis", 0, 0, getWidth(), 30, juce::Justification::centred, 1);
}

void SinensisAudioProcessorEditor::resized()
{
    const int marge_haute_slider = 60;

    cutoffFrequencySlider.setBounds({ 10, marge_haute_slider, 100, 100 });
    cutoffFrequencyLabel.setBounds({ cutoffFrequencySlider.getX() - 10,
                                    cutoffFrequencySlider.getY() - 30,
                                    200, 50 });

    ratioSlider.setBounds({ 100, marge_haute_slider, 100, 100 });
    ratioLabel.setBounds({ ratioSlider.getX() + 30,
                                    ratioSlider.getY() - 30,
                                    200, 50 });

    QSlider.setBounds({ 190, marge_haute_slider, 100, 100 });
    QLabel.setBounds({ QSlider.getX() + 35,
                                    QSlider.getY() - 30,
                                    200, 50 });

    numberOfBandSlider.setBounds({ 275, marge_haute_slider, 100, 100 });
    numberOfBandLabel.setBounds({ numberOfBandSlider.getX() - 5,
                                    numberOfBandSlider.getY() - 30,
                                    200, 50 });

    bandModeButton.setBounds({ 275, marge_haute_slider + 100, 100, 100 });

    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

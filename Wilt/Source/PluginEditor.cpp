/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
WiltAudioProcessorEditor::WiltAudioProcessorEditor (WiltAudioProcessor& p, juce::AudioProcessorValueTreeState& apvts)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    feedbackSlider.setLookAndFeel(&otherLookAndFeel);

    feedbackSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);

    feedbackAttachement.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(apvts, "FEEDBACK", feedbackSlider));

    feedbackSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, feedbackSlider.getTextBoxHeight());

    feedbackLabel.setColour(juce::Label::textColourId, juce::Colours::black);

    feedbackLabel.setText("Feedback", juce::dontSendNotification);

    speedSlider.setLookAndFeel(&otherLookAndFeel);    
    speedSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    speedAttachement.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(apvts, "SPEED", speedSlider));
    speedSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, speedSlider.getTextBoxHeight());
    speedLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    speedLabel.setText("Speed", juce::dontSendNotification);


    //back_ground_color = juce::Colours::darkgrey;


    addAndMakeVisible(feedbackSlider);
    addAndMakeVisible(feedbackLabel);


    addAndMakeVisible(speedSlider);
    addAndMakeVisible(speedLabel);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

WiltAudioProcessorEditor::~WiltAudioProcessorEditor()
{
}

//==============================================================================
void WiltAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void WiltAudioProcessorEditor::resized()
{

    feedbackSlider.setBounds(100, 100, 100, 100);
    speedSlider.setBounds(100, 200, 100, 100);
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

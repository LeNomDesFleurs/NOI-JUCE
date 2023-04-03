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
    const int text_box_width = 50;
    /*
    //------------------------------------------------------
    addAndMakeVisible(outputVolumeSlider);
    outputVolumeSlider.setLookAndFeel(&otherLookAndFeel);
    outputVolumeSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    outputVolumeAttachement.reset(
        new juce::AudioProcessorValueTreeState::SliderAttachment
        (vts, "OUTPUTVOLUME", outputVolumeSlider));
    outputVolumeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, text_box_width, outputVolumeSlider.getTextBoxHeight());

    //FrequencyStuff.setVisible(*vts.getRawParameterValue("MIDIMODE") == 0);
    addAndMakeVisible(outputVolumeLabel);
    outputVolumeLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    outputVolumeLabel.setText("Out Volume",
        juce::dontSendNotification);

    //--------------------------------------------------------
    */
addAndMakeVisible(title);
addAndMakeVisible(bandControl);
addAndMakeVisible(Q);
addAndMakeVisible(midiMode);

    setSize(1200, 400);
}

SinensisAudioProcessorEditor::~SinensisAudioProcessorEditor()
{
}

//==============================================================================
void SinensisAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
   // g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.fillAll(juce::Colours::grey);
    g.setColour (juce::Colours::black);
    //g.setFont (15.0f);
   //g.drawFittedText("Sinensis", 0, 0, getWidth(), 30, juce::Justification::centred, 1);

}

void SinensisAudioProcessorEditor::resized()
{
    const int marge_haute_slider = 60;
    /*
    midiOffButton.setBounds(200, 200, 0, 25);
    midiOffButton.changeWidthToFitText();
    midiMonoButton.setBounds(200, 200 + 25, 0, 25);
    midiMonoButton.changeWidthToFitText();
    midiPolyButton.setBounds(200, 200 + 50, 0, 25);
    midiPolyButton.changeWidthToFitText();

    lowHighButton.setBounds(400, 200, 0, 25);
    lowHighButton.changeWidthToFitText();
    oddEvenButton.setBounds(400, 200 + 25, 0, 25);
    oddEvenButton.changeWidthToFitText();
    peakButton.setBounds(400, 200 + 50, 0, 25);
    peakButton.changeWidthToFitText();

    outputVolumeSlider.setBounds({ 10, marge_haute_slider + 100, 50, 50 });
    outputVolumeLabel.setBounds({ outputVolumeSlider.getX() - 8, outputVolumeSlider.getY() - 30, 200, 50 });

    cutoffFrequencySlider.setBounds({ 10, marge_haute_slider, 100, 100 });
    cutoffFrequencyLabel.setBounds({ cutoffFrequencySlider.getX() - 8, cutoffFrequencySlider.getY() - 30, 200, 50 });

    ratioSlider.setBounds({ 100, marge_haute_slider, 100, 100 });
    ratioLabel.setBounds({ ratioSlider.getX() + 30, ratioSlider.getY() - 30,200, 50 });

    QSlider.setBounds({ 190, marge_haute_slider, 100, 100 });
    QLabel.setBounds({ QSlider.getX() + 10, QSlider.getY() - 30, 200, 50 });

    BandSelectorSlider.setBounds({ 275, marge_haute_slider, 100, 100 });
    BandSelectorLabel.setBounds({ BandSelectorSlider.getX() - 5, BandSelectorSlider.getY() - 30,200, 50 });

    attackSlider.setBounds({ 400, marge_haute_slider, 70, 70 });
    attackLabel.setBounds({ attackSlider.getX() - 5, attackSlider.getY() - 30,200, 50 });

    decaySlider.setBounds({ 400, marge_haute_slider + 70, 70, 70 });
    decayLabel.setBounds({ decaySlider.getX() - 5, decaySlider.getY() - 30,200, 50 });

   // cutoffFrequencyAttachment = 5000.f;
   */
    auto bounds = getLocalBounds();

    bounds.reduce(20, 20);

    midiMode.setBounds(bounds.removeFromLeft(300));
    title.setBounds(bounds.removeFromTop(100));
    bandControl.setBounds(bounds.removeFromRight(600));
    Q.setBounds(bounds);


}

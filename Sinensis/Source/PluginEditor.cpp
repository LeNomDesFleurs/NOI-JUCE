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
    //------------------------------------------------------
    //FrequencyStuff.addAndMakeVisible(cutoffFrequencySlider);
    addAndMakeVisible(cutoffFrequencySlider);
    cutoffFrequencySlider.setLookAndFeel(&otherLookAndFeel);
    cutoffFrequencySlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    cutoffFrequencyAttachement.reset(
        new juce::AudioProcessorValueTreeState::SliderAttachment
        (vts, "root_frequency", cutoffFrequencySlider));
    cutoffFrequencySlider.setTextBoxStyle(juce::Slider::NoTextBox, false, text_box_width, cutoffFrequencySlider.getTextBoxHeight());

    //FrequencyStuff.setVisible(*vts.getRawParameterValue("MIDIMODE") == 0);
    addAndMakeVisible(cutoffFrequencyLabel);
    cutoffFrequencyLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    cutoffFrequencyLabel.setText("Root Frequency",
        juce::dontSendNotification);
    //------------------------------------------------------
 //FrequencyStuff.addAndMakeVisible(cutoffFrequencySlider);
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
    //-------------------------------------------------------
    addAndMakeVisible(ratioSlider);
    ratioSlider.setLookAndFeel(&otherLookAndFeel);
    ratioSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    ratioAttachement.reset(
        new juce::AudioProcessorValueTreeState::SliderAttachment
        (vts, "RATIO", ratioSlider));
    ratioSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, text_box_width, ratioSlider.getTextBoxHeight());

    addAndMakeVisible(ratioLabel);
    ratioLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    ratioLabel.setText("Ratio", juce::dontSendNotification);
    //-------------------------------------------------------
    addAndMakeVisible(QSlider);
    QSlider.setLookAndFeel(&otherLookAndFeel);
    QSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    QAttachement.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(vts, "RESONANCE", QSlider));
    QSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, text_box_width, QSlider.getTextBoxHeight());

    addAndMakeVisible(QLabel);
    QLabel.setText("Resonance", juce::dontSendNotification);
    QLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    //-------------------------------------------------------
    addAndMakeVisible(BandSelectorSlider);
    BandSelectorSlider.setLookAndFeel(&otherLookAndFeel);
    BandSelectorSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    BandSelectorAttachement.reset(
        new juce::AudioProcessorValueTreeState::SliderAttachment
        (vts, "band_selector", BandSelectorSlider));
    BandSelectorSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, text_box_width, BandSelectorSlider.getTextBoxHeight());


    addAndMakeVisible(BandSelectorLabel);
    BandSelectorLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    BandSelectorLabel.setText("Band Selector", juce::dontSendNotification);
    //--------------------------------------------------------
    addAndMakeVisible(attackSlider);
    attackSlider.setLookAndFeel(&otherLookAndFeel);
    attackSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    attackAttachement.reset(
        new juce::AudioProcessorValueTreeState::SliderAttachment
        (vts, "ATTACK", attackSlider));
    attackSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, text_box_width, attackSlider.getTextBoxHeight());


    addAndMakeVisible(attackLabel);
    attackLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    attackLabel.setText("Attack", juce::dontSendNotification);
    //--------------------------------------------------------
    addAndMakeVisible(decaySlider);
    decaySlider.setLookAndFeel(&otherLookAndFeel);
    decaySlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    decayAttachement.reset(
        new juce::AudioProcessorValueTreeState::SliderAttachment
        (vts, "DECAY", decaySlider));
    //BandSelectorSlider.TextEntryBoxPosition(NoTextBox);
    decaySlider.setTextBoxStyle(juce::Slider::NoTextBox, false, text_box_width, decaySlider.getTextBoxHeight());


    addAndMakeVisible(decayLabel);
    decayLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    decayLabel.setText("Decay", juce::dontSendNotification);
    //midiButton.reset(new juce::AudioProcessorValueTreeState::ButtonAttachment(vts, "midi", midiButton));

    addAndMakeVisible(midiOffButton);
    midiOffButtonAttachement.reset(new juce::AudioProcessorValueTreeState::ButtonAttachment(vts, "MIDIOFF", midiOffButton));
    midiOffButton.setClickingTogglesState(true);

    addAndMakeVisible(midiMonoButton);
    midiMonoButtonAttachement.reset(new juce::AudioProcessorValueTreeState::ButtonAttachment(vts, "MIDIMONO", midiMonoButton));
    midiMonoButton.setClickingTogglesState(true);

    addAndMakeVisible(midiPolyButton);
    midiPolyButtonAttachement.reset(new juce::AudioProcessorValueTreeState::ButtonAttachment(vts, "MIDIPOLY", midiPolyButton));
    midiPolyButton.setClickingTogglesState(true);

    midiOffButton.setRadioGroupId(1);
    midiMonoButton.setRadioGroupId(1);
    midiPolyButton.setRadioGroupId(1);

    addAndMakeVisible(lowHighButton);
    lowHighButtonAttachement.reset(new juce::AudioProcessorValueTreeState::ButtonAttachment(vts, "LOWHIGH", lowHighButton));
    lowHighButton.setClickingTogglesState(true);

    addAndMakeVisible(oddEvenButton);
    oddEvenButtonAttachement.reset(new juce::AudioProcessorValueTreeState::ButtonAttachment(vts, "ODDEVEN", oddEvenButton));
    oddEvenButton.setClickingTogglesState(true);

    addAndMakeVisible(peakButton);
    peakButtonAttachement.reset(new juce::AudioProcessorValueTreeState::ButtonAttachment(vts, "PEAK", peakButton));
    peakButton.setClickingTogglesState(true);

    lowHighButton.setRadioGroupId(2);
    oddEvenButton.setRadioGroupId(2);
    peakButton.setRadioGroupId(2);

    //addAndMakeVisible(MidiChoice);
    //setSize(480, 190);
    setSize(480, 300);
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
    g.setFont (15.0f);

    g.drawFittedText("Sinensis", 0, 0, getWidth(), 30, juce::Justification::centred, 1);

}

void SinensisAudioProcessorEditor::resized()
{
    const int marge_haute_slider = 60;
    
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



}
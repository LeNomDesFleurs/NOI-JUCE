/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Filter.h"
#include "Sinensis.h"

//==============================================================================
/**
*/
class SinensisAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    SinensisAudioProcessor();
    ~SinensisAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    //==============================================================================
    juce::AudioProcessorValueTreeState parameters;
    std::atomic <float>* cutoffFrequencyParameter = nullptr;
    std::atomic <float>* QParameter = nullptr;
    std::atomic <float>* ratioParameter = nullptr;
    std::atomic <float>* BandSelectorParameter = nullptr;
    std::atomic <float>* bandModeParameter = nullptr;
    std::atomic <float>* bandSelectorModeParameter = nullptr;
    std::atomic <float>* midiParameter = nullptr;
    int m_note = 0;

    Sinensis::Parameters sinensis_parameters {218.,0.707, 3., 1.5, false, 0.0};
    Sinensis sinensis[2] = { Sinensis(sinensis_parameters), Sinensis(sinensis_parameters) };


   


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SinensisAudioProcessor)
};

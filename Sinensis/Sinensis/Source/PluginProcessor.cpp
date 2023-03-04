/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Filter.h"


//==============================================================================
SinensisAudioProcessor::SinensisAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (
         BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
#endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
#endif
       ),
#else
    :
#endif
parameters(*this, nullptr, juce::Identifier("PARAMETERS"), {
    std::make_unique<juce::AudioParameterFloat>(
        "cutoff_frequency",
        "cutoff Frequency",
        juce::NormalisableRange{20.f, 20000.f, 0.1f, 0.2f, false}, 500.f),

    std::make_unique<juce::AudioParameterFloat>(
        "ratio",
        "Ratio",
        juce::NormalisableRange{0.5f, 2.0f, 0.1f}, 1.5f),

    std::make_unique<juce::AudioParameterFloat>(
        "Q",
        "Q",
        juce::NormalisableRange{0.7f, 40.0f, 0.1f}, 1.0f),

    std::make_unique<juce::AudioParameterFloat>(
        "number_of_band",
        "Number Of Band",
        juce::NormalisableRange{1.0f, 6.0f, 0.1f}, 2.5f)})
    {
        cutoffFrequencyParameter = parameters.getRawParameterValue("cutoff_frequency");
        ratioParameter = parameters.getRawParameterValue("ratio");
        QParameter = parameters.getRawParameterValue("Q");
        numberOfBandParameter = parameters.getRawParameterValue("number_of_band");
    }





SinensisAudioProcessor::~SinensisAudioProcessor()
{
}

//==============================================================================
const juce::String SinensisAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SinensisAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SinensisAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SinensisAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SinensisAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SinensisAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SinensisAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SinensisAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SinensisAudioProcessor::getProgramName (int index)
{
    return {};
}

void SinensisAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SinensisAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    for (int channel = 0; channel < 2; channel++){
        for (int j = 0; j < 6; j++){

            bpf[channel][j].setSamplingFrequency(static_cast <float> (sampleRate));

        }
    }
}

void SinensisAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SinensisAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SinensisAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

        //retrieve param
        //Q
        auto Q = QParameter->load();
        //Number of band
        auto numberOfBand = numberOfBandParameter->load();
        //Ratio
        auto ratio = ratioParameter->load();
        //frequence
        auto frequence = cutoffFrequencyParameter->load();

 

    //process filter
    for (auto channel = 0; channel < buffer.getNumChannels(); ++channel) {
        if (ratio < 0) { ratio = 1 / -ratio; }
        for (int i = 0; i < numberOfBand; i++) {
            //multiply frequence by ratio
            float thisBandFreq = frequence;
            for (int j = 1; j <= i; j++) { thisBandFreq *= ratio; }
            thisBandFreq = truncf(thisBandFreq);
            //frequency folding
            while (thisBandFreq > 15000.f || thisBandFreq < 30.f) {
                if (thisBandFreq > 15000.F) { thisBandFreq = 15000.f - (thisBandFreq - 15000.f); }
                if (thisBandFreq < 30.f) { thisBandFreq = 30.f + (30.f - thisBandFreq); }
            }
            //setParam only compute if params are different
            bpf[channel][i].setParam(thisBandFreq, Q);
        }
        // to access the sample in the channel as a C-style array
        auto channelSamples = buffer.getWritePointer(channel);

        // for each sample in the channel
        for (auto n = 0; n < buffer.getNumSamples(); ++n) {
            const auto input = channelSamples[n];
            auto output = 0.0f;
            for (int i = 0; i < numberOfBand; i++) {
                float j = static_cast<float> (i);
                if (numberOfBand - j < 1) {
                    output += (bpf[channel][i].process(input) / numberOfBand) * (numberOfBand - j);
                }
                else {
                    output += bpf[channel][i].process(input) / (numberOfBand);
                }
            }

            channelSamples[n] = output;
        }
    }
 
}

//==============================================================================
bool SinensisAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SinensisAudioProcessor::createEditor()
{
    return new SinensisAudioProcessorEditor(*this, parameters);
}

//==============================================================================
void SinensisAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SinensisAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SinensisAudioProcessor();
}

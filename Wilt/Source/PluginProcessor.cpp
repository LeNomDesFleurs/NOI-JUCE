/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
WiltAudioProcessor::WiltAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
         .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
         .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
     ), parameters(*this, nullptr, "PARAMETERS", createParams())
#endif
{}

WiltAudioProcessor::~WiltAudioProcessor()
{
}

//==============================================================================
const juce::String WiltAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool WiltAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool WiltAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool WiltAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double WiltAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int WiltAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int WiltAudioProcessor::getCurrentProgram()
{
    return 0;
}

void WiltAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String WiltAudioProcessor::getProgramName (int index)
{
    return {};
}

void WiltAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void WiltAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void WiltAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool WiltAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void WiltAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
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
    setParam();

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelSamples = buffer.getWritePointer (channel);

        for (auto n = 0; n < buffer.getNumSamples(); ++n) {
            const auto input = channelSamples[n];
            channelSamples[n] = wilt[channel].processSample(input);
        }

        // ..do something to the data...
    }
}

//==============================================================================
bool WiltAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* WiltAudioProcessor::createEditor()
{
    return new WiltAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void WiltAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void WiltAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new WiltAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout WiltAudioProcessor::createParams()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

   params.push_back(std::make_unique <juce::AudioParameterFloat>("OUTPUTVOLUME", "Ouput Volume", juce::NormalisableRange{ 0.0f, 2.0f, 0.01f }, 0.6f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("SPEED", "Speed", juce::NormalisableRange<float> { -2.f, 2.0f, 0.1f }, 1.f));
    //params.push_back(std::make_unique<juce::AudioParameterFloat>("REDUX", "Redux", juce::NormalisableRange<float> { -2.f, 3.0f, 0.1f }, 0.4f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FEEDBACK", "Feedback", juce::NormalisableRange<float> { 0.1f, 0.99f, 0.01f }, 0.8f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DRYWET", "DrYWet", juce::NormalisableRange<float> { 0.f, 1.f, 0.01f }, 1.f));

  

    return { params.begin(), params.end() };
}


void WiltAudioProcessor::setParam() {
 
    //PARAM
    wilt_parameters.speed = *parameters.getRawParameterValue("SPEED");
    wilt_parameters.feedback = *parameters.getRawParameterValue("FEEDBACK");
    wilt_parameters.dry_wet = *parameters.getRawParameterValue("DRYWET");
    //wilt_parameters.output_volume = *parameters.getRawParameterValue("OUTPUTVOLUME");
    //SET OBJECT
    wilt[0].setParameters(wilt_parameters);
    wilt[1].setParameters(wilt_parameters);
}
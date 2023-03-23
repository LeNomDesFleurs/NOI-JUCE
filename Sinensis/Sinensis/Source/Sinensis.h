/*
  ==============================================================================

    Sinensis.h
    Created: 4 Mar 2023 5:01:48pm
    Author:  thoma

  ==============================================================================
*/

#pragma once
#include "Filter.h"
#include "JuceHeader.h"

class Sinensis {
public:
    ///<summary> Parameters of Sinensis </summary>
        /// <param name = "frequency"> </param>
        /// @param float Q
        /// @param float band_selector
        /// @param float ratio
        /// @param bool gain_Q_link
        /// @param float band_selector_mode
    struct Parameters{
        int midi_mode;
        int band_selector_mode;
        float root_frequency;
        float resonance;
        float band_selector;
        float ratio;
        float attack;
        float decay;
    };
    Sinensis();
    ~Sinensis();
    void setParameters(Sinensis::Parameters parameters);
    float processSample(float input);
    float processSinensis(float input, juce::MidiBuffer& midi_buffer);
    void prepareMidiOff();
    void prepareMidiMono(juce::MidiBuffer& midi_buffer);
    void prepareMidiPoly(juce::MidiBuffer& midi_buffer);

    void computeGain();
        void computeLowHigh();
        void computeOddEven();
        void computePeak();
        void processEnvelope(int envelope_index);
    void computeEnvelopesStep();

    void computeQ();
    void prepareBpf();
        void computeFrequencyMidiOff();
        void computeFrequencyMidiMono();
        void computeFrequencyMidiPoly();

    void extractMidiMono(juce::MidiBuffer& midi_buffer);
    void extractMidiPoly(juce::MidiBuffer& midi_buffer);

    void setSamplingFrequency(float sampling_frequency);

private:
    Sinensis::Parameters m_parameters;
    noi::Filter::BPF m_bpf[6];
    float m_sampling_frequency;
    float m_Q[6];
    float m_frequency[6];
    float m_gain[6];
    float m_attack_step;
    float m_decay_step;
    float m_envelope_statut[6];
    //int m_notes[6];
    juce::SortedSet<int> m_notes;

};
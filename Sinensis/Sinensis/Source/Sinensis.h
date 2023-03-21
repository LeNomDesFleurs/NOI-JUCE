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
        float frequency;
        float resonance;
        float band_selector;
        float ratio;
        float attack;
        float decay;
    };
    Sinensis(Sinensis::Parameters parameters);
    ~Sinensis();
    void setParameters(Sinensis::Parameters parameters);
    float processSample(float input, juce::MidiBuffer& midi_buffer);
    void computeGain();
        void computeLowHigh();
        void computeOddEven();
        void computePeak();
    void computeAttackStep();
    void computeDecayStep();
    void computeQ();
    void prepareBpf();
    void computeFrequency();
        void computeFrequencyMidiOff();
        void computeFrequencyMidiMono();
        void computeFrequencyMidiPoly();

    void setSamplingFrequency(float sampling_frequency);

private:
    Sinensis::Parameters m_parameters;
    noi::Filter::BPF m_bpf[6];
    float sampling_frequency;
    float m_Q[6];
    float m_frequency[6];
    float m_gain[6];
    float m_attack_step;
    float m_decay_step;
    float m_enveloppe_statut[6];

};
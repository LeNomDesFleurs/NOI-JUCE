/*
  ==============================================================================

    Sinensis.h
    Created: 4 Mar 2023 5:01:48pm
    Author:  thoma

  ==============================================================================
*/

#pragma once
#include "Filter.h"

class Sinensis {
public:
    struct Parameters{
        float frequency;
        float Q;
        float band_selector;
        float ratio;
        bool gain_Q_link;
        int band_selector_mode;

    };
    Sinensis(Sinensis::Parameters parameters);
    Sinensis();
    ~Sinensis();
    void setParameters(Sinensis::Parameters parameters);
    float processSample(float input);
    void computeGain();
        void computeLowHigh();
        void computeOddEven();
    void computeQ();
    void prepareBpf();
    void computeFrequency();
    void setSamplingFrequency(float sampling_frequency);

private:
    Sinensis::Parameters m_parameters;
    noi::Filter::BPF m_bpf[6];
    float m_Q[6];
    float m_frequency[6];
    float m_gain[6];

};
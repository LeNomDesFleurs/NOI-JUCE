/*
  ==============================================================================

    Sinensis.cpp
    Created: 4 Mar 2023 5:01:37pm
    Author:  thoma

  ==============================================================================
*/

#include "Sinensis.h"

Sinensis::Sinensis(Sinensis::Parameters parameters) {
    m_parameters = parameters;
}
Sinensis::Sinensis() {

};

Sinensis::~Sinensis() {

}

void Sinensis::setParameters(Sinensis::Parameters parameters) {
    m_parameters = parameters;
}

float Sinensis::processSample(float input){
    computeFrequency();
    computeGain();
    computeQ();
    prepareBpf();
    float output = 0;
    for (int i = 0; i < 6; i++) {
        output += m_bpf[i].process(input) * m_gain[i];
    }
    if (output > 1.0f) output = 1.0f;
    if (output < -1.0f) output = -1.0f;
    return output;
}

void Sinensis::computeFrequency() {
   // if (m_parameters.ratio < 0) { m_parameters.ratio = 1 / -m_parameters.ratio; }
    for (int i = 0; i < 6; i++) {
        //multiply frequence by ratio
        float thisBandFreq = m_parameters.frequency;
        for (int j = 1; j <= i; j++) { thisBandFreq *= m_parameters.ratio; }
        thisBandFreq = truncf(thisBandFreq);
        //frequency folding
        while (thisBandFreq > 15000.f || thisBandFreq < 30.f) {
            if (thisBandFreq > 15000.F) { thisBandFreq = 15000.f - (thisBandFreq - 15000.f); }
            if (thisBandFreq < 30.f) { thisBandFreq = 30.f + (30.f - thisBandFreq); }
        }
        m_frequency[i] = thisBandFreq;
    }
}

void Sinensis::computeGain() {
    for (int i = 0; i < 6; i++) {
   
        m_gain[i] = m_parameters.band_selector;
    }
  // switch (m_parameters.band_selector_mode){
  // case 0:computeLowHigh();
  // case 1:computeOddEven();
  // }
    //computeOddEven();
}

void Sinensis::computeLowHigh() {
    float band_selector = m_parameters.band_selector;
    float alpha = band_selector * 2.0f - 1.0f;
    float beta =  (- 2.0f * (band_selector * band_selector)) + (2.0f * band_selector);
    band_selector *= 6.0f;

    for (int i = 0; i < 6; i++) {
        float this_band_index = static_cast<float> (i);
        this_band_index /= 5.0f;
        float this_band_gain = (this_band_index) * alpha + beta;
        if (this_band_gain < 0.0f) {
            this_band_gain = 0.0f;
        }
        m_gain[i] = this_band_gain;
    }
}

void Sinensis::computeOddEven() {
    for (int i = 0; i < 6; i++) {
        float this_band_gain = 0;
        //odd case
        if (i == 0 || i == 2 || i == 4) {
            this_band_gain = m_parameters.band_selector;
        }
        //even case
        if (i == 1 || i == 3 || i == 5) {
            this_band_gain = 1.0f - m_parameters.band_selector;
        }
        m_gain[i] = this_band_gain;
    }
}

void Sinensis::computeQ() {
    if (m_parameters.gain_Q_link) {
        for (int i = 0; i < 6; i++) {
            m_Q[i] = m_gain[i] * m_parameters.Q;
        }
        return;
    }
    for (int i = 0; i < 6; i++) {
        m_Q[i] = m_parameters.Q;
    }
}


void Sinensis::prepareBpf() {
    for (int i = 0; i < 6; i++) {
        m_bpf[i].setParam(m_frequency[i], m_Q[i]);
    }
}

void Sinensis::setSamplingFrequency(float sampling_frequency) {
    for (auto bpf : m_bpf) bpf.setSamplingFrequency(sampling_frequency);
  
}
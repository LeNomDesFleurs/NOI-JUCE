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
    computeFrequency();
    computeGain();
    computeQ();
    prepareBpf();
}

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

  int selector = static_cast<int> (m_parameters.band_selector_mode);
   
  switch (selector){
  case 0:computeLowHigh(); break;
  case 1:computeOddEven(); break;
  case 2:computePeak(); break;
  }

}

void Sinensis::computeLowHigh() {
    float band_selector = m_parameters.band_selector;
    float alpha = band_selector * 4.0f - 2.0f;
    float beta = -2.0f*(band_selector * band_selector) + 1.0;

    for (int i = 0; i < 6; i++) {
        float this_band_index = static_cast<float> (i);
        this_band_index /= 5.0f;
        float this_band_gain = this_band_index * alpha + beta;
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

void Sinensis::computePeak() {
        float cursor = m_parameters.band_selector;
        cursor *= 5.;
        for (int i = 0; i < 6; i++) {
            float band_index = static_cast<float> (i);
            float band_gain = 0.0f;
            if (cursor < band_index) {
                band_gain = band_index - cursor;
            }
            else { band_gain = cursor - band_index; }
            
            band_gain = 1 - band_gain;
            if (band_gain > 1.) { band_gain = 1.; }
            if (band_gain < 0.) { band_gain = 0.; }
            //calculer proximiter avec curseur
            m_gain[i] = band_gain;
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
        float Q = (m_parameters.Q * m_gain[i]) + 0.707;
        if (Q > 32.) Q = 32.0f;
        m_Q[i] = Q;
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
/*
  ==============================================================================

    Wilt.cpp
    Created: 14 Mar 2023 3:34:13pm
    Author:  thoma

  ==============================================================================
*/

#include "Wilt.h"

		
Wilt::Wilt() {
	ap1.setReadSpeed(1.0);
	ap2.setReadSpeed(1.0);
	cb1.setReadSpeed(1.0);
	cb2.setReadSpeed(1.0);
	cb3.setReadSpeed(1.0);
	cb4.setReadSpeed(1.0);
}
inline float Wilt::processRedux(float input) {
	if (counter >= m_parameters.redux) { counter = 0; return input; }
	counter++;

}
inline void Wilt::setSpeed() {
	ap1.setReadSpeed(m_parameters.speed);
	ap2.setReadSpeed(m_parameters.speed);
	cb1.setReadSpeed(m_parameters.speed);
	cb2.setReadSpeed(m_parameters.speed);
	cb3.setReadSpeed(m_parameters.speed);
	cb4.setReadSpeed(m_parameters.speed);
}
void Wilt::setTime() {
	ap1.overrideFeedback(m_parameters.feedback);
	ap2.overrideFeedback(m_parameters.feedback);
	cb1.overrideFeedback(m_parameters.feedback);
	cb2.overrideFeedback(m_parameters.feedback);
	cb3.overrideFeedback(m_parameters.feedback);
	cb4.overrideFeedback(m_parameters.feedback);
}
void Wilt::setParameters(Parameters parameters) { m_parameters = parameters; }

float Wilt::processSample(float input) {
	//input = processRedux(input);
	setSpeed();
	setTime();


	float b0 = input;
	float c1 = cb1.process(b0);
	float c2 = cb2.process(b0);
	float c3 = cb3.process(b0);
	float c4 = cb4.process(b0);
	float comb_sum = (c1 + c2 + c3 + c4) / 4.f;
	comb_sum = ap1.process(comb_sum);
	comb_sum = ap2.process(comb_sum);
	return noi::Outils::dryWet(input, comb_sum, m_parameters.dry_wet);
}
/*
  ==============================================================================

    Wilt.h
    Created: 14 Mar 2023 3:34:13pm
    Author:  thoma

  ==============================================================================
*/

#pragma once
#include "outils.hpp"
#include "filter.h"
#include <math.h>

class Wilt {
public:
	struct Parameters{
		float speed;
		float feedback;
		float dry_wet;
		float redux;
	};
	Wilt();
	float processRedux(float input);
	void setSpeed();
	void setTime();
	void setParameters(Parameters parameters);
	float processSample (float input);
private:
		Parameters m_parameters;
		int counter{};
		noi::Filter::Allpass ap1{ 0.0017 };
		noi::Filter::Allpass ap2{ 0.005 };
		noi::Filter::Comb cb1{ 0.0297 };
		noi::Filter::Comb cb2{ 0.0371 };
		noi::Filter::Comb cb3{ 0.0411 };
		noi::Filter::Comb cb4{ 0.0437 };

};/*Wilt*/

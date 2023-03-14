/*
  ==============================================================================

    Wilt.h
    Created: 14 Mar 2023 3:34:13pm
    Author:  thoma

  ==============================================================================
*/

#pragma once
#include "outils.hpp"
#include "filter.hpp"
#include <math.h>

namespace noi {

	namespace Reverb {

		class Wilt {
			struct Parameters{
				float speed;
				float feedback;
				float dry_wet;
				float redux;
			};

		public:
			Schroeder() {
				ap1.setReadSpeed(1.0);
				ap2.setReadSpeed(1.0);
				cb1.setReadSpeed(1.0);
				cb2.setReadSpeed(1.0);
				cb3.setReadSpeed(1.0);
				cb4.setReadSpeed(1.0);
			}
			inline float processRedux(float input) {
				if (counter >= repeats) { counter = 0; redux_output = redux_input; }
				counter++;
			}
			inline void setSpeed() {
				ap1.setReadSpeed(m_parameters.speed);
				ap2.setReadSpeed(m_parameters.speed);
				cb1.setReadSpeed(m_parameters.speed);
				cb2.setReadSpeed(m_parameters.speed);
				cb3.setReadSpeed(m_parameters.speed);
				cb4.setReadSpeed(m_parameters.speed);
			}
			void setTime() {
				ap1.overrideFeedback(m_parameters.feedback);
				ap2.overrideFeedback(m_parameters.feedback);
				cb1.overrideFeedback(m_parameters.feedback);
				cb2.overrideFeedback(m_parameters.feedback);
				cb3.overrideFeedback(m_parameters.feedback);
				cb4.overrideFeedback(m_parameters.feedback);
			}
			void setDryWet(float DryWet) { m_DryWet = DryWet; }
			float process(float input) {
				input = processRedux(input);

				

				schroeder.setDryWet(params[DW_PARAM].getValue());
				schroeder.setTime(params[RT60_PARAM].getValue());
				schroeder.setStep(speed);
				rvb_output = schroeder.process(rvb_input);

				float b0 = input;
				float c1 = cb1.process(b0);
				float c2 = cb2.process(b0);
				float c3 = cb3.process(b0);
				float c4 = cb4.process(b0);
				float comb_sum = (c1 + c2 + c3 + c4) / 4.f;
				comb_sum = ap1.process(comb_sum);
				comb_sum = ap2.process(comb_sum);
				return noi::Outils::dryWet(input, comb_sum, m_DryWet);
			}

		private:
			Parameters m_parameters;

			noi::Filter::Allpass ap1{ 0.0017 };
			noi::Filter::Allpass ap2{ 0.005 };
			noi::Filter::Comb cb1{ 0.0297 };
			noi::Filter::Comb cb2{ 0.0371 };
			noi::Filter::Comb cb3{ 0.0411 };
			noi::Filter::Comb cb4{ 0.0437 };

		};/*Schroeder*/

		filter_input = rm_output;
		lpf.setParam(params[TONE_PARAM].getValue());
		filter_output = lpf.process(filter_input);




	}
}
/*
  ==============================================================================

    Hellebore.cpp
    Created: 11 Mar 2023 2:28:30pm
    Author:  thoma

  ==============================================================================
*/

#include "Hellebore.h"

#include "plugin.hpp"
#include "reverb.hpp"
#include "outils.hpp"
#include <array>

struct Hellebore : Module {

	enum ParamId {
	SIZE_PARAM,
	VARIATION_PARAM,
	TIME_PARAM,
	DRYWET_PARAM,
	FREEZE_PARAM,

	SIZE_CV_PARAM,
	VARIATION_CV_PARAM,
	TIME_CV_PARAM,

	PARAMS_LEN
	};
	enum InputId {
	FREEZE_CV_INPUT,
	VARIATION_CV_INPUT,
	TIME_CV_INPUT,
	SIZE_CV_INPUT,
	L_INPUT,
	R_INPUT,
	INPUTS_LEN
	};
	enum OutputId {
	L_OUTPUT,
	R_OUTPUT,
	TEST_OUTPUT,
	OUTPUTS_LEN
	};
	enum LightId {
	FREEZE_LIGHT,
	LIGHTS_LEN
	};

	Hellebore() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);

		configParam(VARIATION_PARAM, 0.f, 0.2f, 0.1, "Variation");
		configParam(SIZE_PARAM, 0.010f, 1.00f, 0.01f, "Size", "s", 4, 0.3, -0.3);
		configParam(TIME_PARAM, 0.1f, 20.f, 10.f, "Time", "s");
		configParam(DRYWET_PARAM, 0.f, 1.f, 1.f, "Drywet", "%", 0.f, 100.f);
		configParam(FREEZE_PARAM, 0, 1, 0, "Freeze");

		configParam(TIME_CV_PARAM, -1.f, 1.f, 0.f, "Time CV", "%", 0,-100.f, 100.f);
		configParam(SIZE_CV_PARAM, -0.01f, 0.01f, 0.f, "Size CV", "%", 0, 10000.f);
		configParam(VARIATION_CV_PARAM, -0.1f, 0.1f, 0.f, "Variation CV", "%",0, 1000.f);

		configInput(FREEZE_CV_INPUT, "Freeze CV");
		configInput(VARIATION_CV_INPUT, "Variation CV");
		configInput(SIZE_CV_INPUT, "Size CV");
		configInput(TIME_CV_INPUT, "Time CV");
		configInput(L_INPUT, "Left");
		configInput(R_INPUT, "Right");

		configOutput(L_OUTPUT, "Left");
		configOutput(R_OUTPUT, "Right");
		configOutput(TEST_OUTPUT, "TEST");
	}

	
	noi::Filter::LPF SlewLPF{20};
	noi::Reverb::StereoMoorer::Parameters m_params{false, 1.F, 0.01f, 0.1f, 10.f};
	noi::Reverb::StereoMoorer moorer = noi::Reverb::StereoMoorer(m_params);
	std::array<float, 2> signal_outputs = {0, 0};
	std::array<float, 2> signal_inputs = {0, 0};

	void process(const ProcessArgs& args) override {

		//freeze
		m_params.freeze = (params[FREEZE_PARAM].getValue() > 0);
		if (inputs[FREEZE_CV_INPUT].isConnected()){
		m_params.freeze = (inputs[FREEZE_CV_INPUT].getVoltage()>0);
		}
		//buffer size
		float combTime_cv = inputs[SIZE_CV_INPUT].getVoltage()*params[SIZE_CV_PARAM].getValue()*10.f;
		combTime_cv = SlewLPF.process(combTime_cv);
		float comb_feedback_time = 0.3 * pow(3.f, params[SIZE_PARAM].getValue()) - 0.3;
		comb_feedback_time += combTime_cv;
		m_params.comb_time = rack::math::clamp(comb_feedback_time, 0.010f, 1.f);
		//variation
		float variation_cv = inputs[VARIATION_CV_INPUT].getVoltage() * params[VARIATION_CV_PARAM].getValue();
		m_params.variation = params[VARIATION_PARAM].getValue() + variation_cv;
		//time
		float time_cv = inputs[TIME_CV_INPUT].getVoltage() * params[TIME_CV_PARAM].getValue();
		m_params.rt60 = rack::math::clamp(params[TIME_PARAM].getValue() + time_cv, 0.1f, 20.f);
		//drywet
		m_params.dry_wet = params[DRYWET_PARAM].getValue();
		//input
 		signal_inputs[0] = inputs[L_INPUT].getVoltage();
 		signal_inputs[1] = inputs[R_INPUT].getVoltage();

		moorer.updateParameters(m_params);
		signal_outputs = moorer.processStereo(signal_inputs);

		outputs[L_OUTPUT].setVoltage(signal_outputs[0]);
		outputs[R_OUTPUT].setVoltage(signal_outputs[1]);

		// outputs[R_OUTPUT].setVoltage(test_out2);
		// outputs[TEST_OUTPUT].setVoltage(test_out);
		lights[FREEZE_LIGHT].setBrightness(m_params.freeze ? 1.f: 0.f);
	}
};
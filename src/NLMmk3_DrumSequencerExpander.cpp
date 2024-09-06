#include "plugin.hpp"

#include "expansion.hpp"

struct NLMmk3_DrumSequencerExpander : Module {
	enum ParamId {
		COLOR_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		INPUT_INPUT,
		RECORD_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		OUTPUT_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHT_CONNECTED_LIGHT,
		LIGHT_LIGHT,
		LIGHTS_LEN
	};


	//MessageSystem messageSystem;

	NLMmk3_DrumSequencerExpander() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(COLOR_PARAM, 0.f, 127.f, 1.f, "Color");
		configInput(INPUT_INPUT, "");
		configInput(RECORD_INPUT, "");
		configOutput(OUTPUT_OUTPUT, "");
		//messageSystem = MessageSystem(ExpansionType::DRUM_SEQUENCER, this);
	}


	void onExpanderChange(const ExpanderChangeEvent& e) override {
		if (e.side == 0 || e.side == 1) {
			DEBUG("ON EXPANDER CHANGE side left/right");
			Module* module = getLeftExpander().module;

			int counter = 0;
			const int MAX_EXPANDERS = 256;
			while  (module != nullptr) {
				counter++;
				if (counter > MAX_EXPANDERS) {
					DEBUG("ERROR: Too many expanders -> Not Fixed Bug :/");
					return;
				}
				if (module->getModel() == modelNLMmk3) {
					// set the newly needed value
					bool* value = (bool*) module->getRightExpander().producerMessage;
					*value = true;

					// no need to request flip, it will be done by the main module
					module->getRightExpander().requestMessageFlip();
					return;
				}
				module = module->getLeftExpander().module;
			}
		} 	
	}


	void process(const ProcessArgs& args) override {
	}
};


struct NLMmk3_DrumSequencerExpanderWidget : ModuleWidget {
	NLMmk3_DrumSequencerExpanderWidget(NLMmk3_DrumSequencerExpander* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/NLMmk3_DrumSequencerExpander.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(5.173, 57.277)), module, NLMmk3_DrumSequencerExpander::COLOR_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.178, 27.978)), module, NLMmk3_DrumSequencerExpander::INPUT_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.271, 39.464)), module, NLMmk3_DrumSequencerExpander::RECORD_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(5.398, 104.421)), module, NLMmk3_DrumSequencerExpander::OUTPUT_OUTPUT));

		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(8.679, 8.377)), module, NLMmk3_DrumSequencerExpander::LIGHT_CONNECTED_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(5.251, 96.894)), module, NLMmk3_DrumSequencerExpander::LIGHT_LIGHT));

		// mm2px(Vec(1.809, 1.86))
		addChild(createWidget<Widget>(mm2px(Vec(4.289, 62.115))));
	}
};


Model* modelNLMmk3_DrumSequencerExpander = createModel<NLMmk3_DrumSequencerExpander, NLMmk3_DrumSequencerExpanderWidget>("NLMmk3_DrumSequencerExpander");
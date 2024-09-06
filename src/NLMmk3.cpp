#include "plugin.hpp"

#include <iostream>
#include <regex>
#include <map>
#include <set>

#include "nl/driver.hpp"
#include "nl/app.hpp"
#include "expansion.hpp"

const std::regex IN_MIDI_NAME_REGEX("^MIDIIN2 \\(LPMiniMK3 MIDI\\).*$");
const std::regex OUT_MIDI_NAME_REGEX("^LPMiniMK3 MIDI.*$");

const std::set<Model *> allowedSubmodules = {
    modelNLMmk3_DrumSequencerExpander
    // ...
};

struct DrumSequencerData {
    float lastParamValue = -1.f;
};

struct NLMmk3 : rack::Module
{
    enum ParamId
    {
        TEMPO_PARAM,
        QUANT_PARAM,
        PARAMS_LEN
    };
    enum InputId
    {
        IN_INPUT,
        INPUTS_LEN
    };
    enum OutputId
    {
        OUT_OUTPUT,
        OUTPUTS_LEN
    };
    enum LightId
    {
        LIGHT_LIGHT,
        LIGHTS_LEN
    };

    rack::midi::Input input;
    rack::midi::Output output;

    std::map<Model *, std::vector<Module *>> expanders;
    std::vector<DrumSequencerData> drumSequencerData;

    nl::Driver driver;
    nl::App app;

    // MessageSystem messageSystem;
    bool initialized = false;

    bool reinitExpanderBuffer[2] = {false, false};

    /* #region INITIALZE */
public:
    NLMmk3()
    {
        config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
        configParam(TEMPO_PARAM, 30.f, 300.f, 60.f, "Tempo", " BPM");
        // configParam(QUANT_PARAM, 0.f, 16.f, 1.0f, "Qunatization", " x", 0.5f);
        configSwitch(QUANT_PARAM, 0.5f, 8.f, 1.f, "Quantization", {"0.5x", "1x", "1.5x", "2x", "2.5x", "3x", "3.5x", "4x", "4.5x", "5x", "5.5x", "6x", "6.5x", "7x", "7.5x", "8x"});
        configInput(IN_INPUT, "Input Clock");
        configOutput(OUT_OUTPUT, "Output Clock");

        configBypass(IN_INPUT, OUT_OUTPUT);
        // messageSystem = MessageSystem(ExpansionType::DRUM_SEQUENCER, this);

        // Configure right Expander

        INFO("RUN EINIT; Main Module");

        getRightExpander().producerMessage = &reinitExpanderBuffer[0];
        getRightExpander().consumerMessage = &reinitExpanderBuffer[1];

        // Initialize MIDI
        app = nl::App();
    }

    bool areDriversInitialized()
    {
        return input.getDeviceId() >= 0 && output.getDeviceId() >= 0;
    }
    void initializeMidi()
    {
        INFO("Initializing NLMmk3 module:");
        input = midi::Input();
        INFO("\tInput devices:");

        int selectedInputDeviceId = -1;
        for (int &i : input.getDeviceIds())
        {
            std::string name = input.getDeviceName(i);
            INFO("\t  %d: %s", i, name.c_str());
            if (std::regex_match(name, IN_MIDI_NAME_REGEX))
            {
                selectedInputDeviceId = i;
            }
        }

        output = midi::Output();

        int selectedOutputDeviceId = -1;
        INFO("\tOutput devices:");
        for (int &i : output.getDeviceIds())
        {
            std::string name = output.getDeviceName(i);
            INFO("\t  %d: %s", i, name.c_str());
            if (std::regex_match(name, OUT_MIDI_NAME_REGEX))
            {
                selectedOutputDeviceId = i;
            }
        }

        if (selectedInputDeviceId >= 0)
        {
            input.setDeviceId(selectedInputDeviceId);
            INFO("\tSelected input device: %s", input.getDeviceName(selectedInputDeviceId).c_str());
        }

        if (selectedOutputDeviceId >= 0)
        {
            output.setDeviceId(selectedOutputDeviceId);
            INFO("\tSelected output device: %s", output.getDeviceName(selectedOutputDeviceId).c_str());
        }

        if (areDriversInitialized())
        {
            driver = nl::Driver(&input, &output);
            driver.initProgrammerMode();

            // const nl::Color colorTable = nl::Color::table(5);
            // const nl::Color colorFlash = nl::Color::flash(5, 0);
            // const nl::Color colorPulse = nl::Color::pulse(64, 32);
            // const nl::Color colorRGB = nl::Color::RGB(127, 0, 127);

            // driver.renderer.setColor(colorTable, 1, 1);
            // driver.renderer.setColor(colorFlash, 2, 2);
            // driver.renderer.setColor(colorPulse, 3, 3);
            // driver.renderer.setColor(colorRGB, 4, 4);

            driver.renderer.flush();
            lights[LIGHT_LIGHT].setBrightness(1.f);
        }
    }

    /* #endregion */

    /* #region EXPAND */

    void onExpanderChange(const ExpanderChangeEvent &e) override
    {

        if (e.side == 1)
        {
            DEBUG("ON EXPANDER CHANGE side right");
            bool *value = (bool *)getRightExpander().producerMessage;
            *value = true;

            // no need to request flip, it will be done by the main module
            getRightExpander().requestMessageFlip();
        }
    }

    void setExpandersConnectedLights(float setToVal)
    {
        for (auto it = this->expanders.begin(); it != this->expanders.end(); ++it)
        {
            auto val = it->second;
            for (auto module : val)
            {
                // set connected to 0
                module->getLight(0).setBrightness(setToVal);
            }
        }
    }

    void collectAllExpanders()
    {
        setExpandersConnectedLights(0.f);
        DEBUG("Clearing expanders");
        printAllExpanders();
        expanders = {};
        drumSequencerData = {};

        DEBUG("Collecting expanders:");
        Module *module = getRightExpander().module;
        while (module != nullptr)
        {
            if (allowedSubmodules.find(module->model) != allowedSubmodules.end())
            {

                float colorParam = module->getParam(0).getValue();
                DEBUG("\tFound expander: %s with color <%d>", module->model->name.c_str(), (int)colorParam); // g

                if (this->expanders.find(module->getModel()) == this->expanders.end())
                {
                    this->expanders[module->getModel()] = {};
                }
                this->expanders[module->getModel()].push_back(module);

                if (module->getModel() == modelNLMmk3_DrumSequencerExpander)
                {
                    
                    drumSequencerData.push_back(DrumSequencerData());
                }
            }
            module = module->getRightExpander().module;
        }
        setExpandersConnectedLights(1.f);
    }

    void printAllExpanders()
    {
        DEBUG("EXPANDER INFO");
        DEBUG("Expander count: %lld", this->expanders.size());

        for (auto it = this->expanders.begin(); it != this->expanders.end(); ++it)
        {
            auto key = it->first;
            auto val = it->second;
            DEBUG("Expander[%lld]: %s", val.size(), key->name.c_str());

            for (auto module : val)
            {
                int color = -1;
                if (module->getModel() == modelNLMmk3_DrumSequencerExpander)
                {
                    color = (int)module->getParam(0).getValue();
                }
                DEBUG("\t%s: color %d", module->model->name.c_str(), color);
            }
        }
    }

    void onExpanderConfigurationChange()
    {
        DEBUG("ON EXPANDER CONFIGURATION CHANGE");
        collectAllExpanders();
        printAllExpanders();

        app.reinit(this->expanders);
        rerender();
    }

    bool isExpanderChanged()
    {
        bool *changed = (bool *)getRightExpander().consumerMessage;

        if (*changed)
        {
            *changed = false;
            return true;
        }

        return false;
    }

    void onRemove() override
    {
        driver.disableProgrammerMode();
    }

    /* #endregion */

    /* #region RENDER */
    void rerender()
    {
        app.render(driver);
    }
    /* #endregion */

    /* #region PROCESS */
    void processParams(const ProcessArgs &args)
    {
        if (isExpanderChanged())
        {
            onExpanderConfigurationChange();
        }


        // update drum sequencers data
        for (size_t i = 0; i < drumSequencerData.size(); i++)
        {
            float paramValue = expanders[modelNLMmk3_DrumSequencerExpander][i]->getParam(0).getValue();
            DrumSequencerData &data = drumSequencerData[i];
            if (data.lastParamValue != paramValue)
            {
                data.lastParamValue = paramValue;
                // send data to drum sequencer
                rerender();
            }
        }
    }

    void process(const ProcessArgs &args) override
    {
        if ((args.frame % 64) == 0)
        {
            processParams(args);
        }

        if (!initialized)
        {
            initializeMidi();
            initialized = true;
        }
    }
    /* #endregion */
};

struct NLMmk3Widget : ModuleWidget
{
    NLMmk3Widget(NLMmk3 *module)
    {
        setModule(module);
        setPanel(createPanel(asset::plugin(pluginInstance, "res/NLMmk3.svg")));

        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

        addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(6.666, 37.036)), module, NLMmk3::TEMPO_PARAM));
        addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(19.501, 37.148)), module, NLMmk3::QUANT_PARAM));

        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(6.388, 25.007)), module, NLMmk3::IN_INPUT));

        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(19.432, 25.106)), module, NLMmk3::OUT_OUTPUT));

        addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(12.566, 22.802)), module, NLMmk3::LIGHT_LIGHT));
    }
};

Model *modelNLMmk3 = createModel<NLMmk3, NLMmk3Widget>("NLMmk3");
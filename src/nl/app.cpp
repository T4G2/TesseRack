#include "app.hpp"

#include "../plugin.hpp"

namespace nl {

    void App::reinit(std::map<rack::Model *, std::vector<rack::Module *>> expanders)
    {
        std::vector<rack::Module *> drumSeqExpanders = expanders[modelNLMmk3_DrumSequencerExpander];
        reinitDrumSequencers(drumSeqExpanders);
    }

    void App::reinitDrumSequencers(std::vector<rack::Module *> drumSeqExpanders)
    {
        drumSeqModules.clear();
        for (auto drumSeqExpander : drumSeqExpanders)
        {
            drumSeqModules.push_back(drumSeqExpander);
        }   
    }

    void App::render(Driver& driver)
    {
        driver.renderer.clear();
        drumSequencerView.renderDrums(driver, drumSeqModules);
        driver.renderer.flush();
    }
} // namespace nl
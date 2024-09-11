#include "app.hpp"

#include "../plugin.hpp"

namespace nl {

    void App::reinit(Driver &driverRef, std::map<rack::Model*, std::vector<rack::Module*>> expanders)
    {
        std::vector<rack::Module *> drumSeqExpanders = expanders[modelNLMmk3_DrumSequencerExpander];
        driver = &driverRef;
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

    void App::render()
    {
        driver->renderer.clear();

        // Select later
        drumSequencerView.render(*this);
        driver->renderer.flush();
    }
} // namespace nl
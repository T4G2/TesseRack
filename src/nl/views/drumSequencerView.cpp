#include "drumSequencerView.hpp"
#include "../color.hpp"

namespace nl {

    void nl::DrumSequencerView::renderDrums(Driver& driver, std::vector<rack::Module*> drumSeqModules) {
        renderModuleMiniatures(driver, drumSeqModules);

    }


    void nl::DrumSequencerView::renderModuleMiniatures(Driver& driver, std::vector<rack::Module*> drumSeqModules) {
        for (size_t i = 0; i < drumSeqModules.size(); i++) {
            rack::Module* module = drumSeqModules[i];
            int colorId = module->getParam(0).getValue();

            Color color = Color::table(colorId);

            driver.renderer.setColor(color, 9, 8-i);
        }
    }

}
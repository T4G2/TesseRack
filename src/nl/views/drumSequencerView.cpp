#include "drumSequencerView.hpp"
#include "../app.hpp"
#include "../color.hpp"

namespace nl {


    void DrumSequencerView::render(App& app) {
        renderDrums(app);
    }


    void nl::DrumSequencerView::renderDrums(App& app) {
        app.driver->renderer.setColor(Color::flash(3,2), 6, 9);
        renderModuleMiniatures(app);

    }


    void nl::DrumSequencerView::renderModuleMiniatures(App& app) {
        for (size_t i = 0; i < app.drumSeqModules.size(); i++) {
            rack::Module* module = app.drumSeqModules[i];
            int colorId = module->getParam(0).getValue();

            Color color = Color::table(colorId);

            app.driver->renderer.setColor(color, 9, 8-i);
        }
    }
}
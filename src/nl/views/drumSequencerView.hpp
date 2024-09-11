#pragma once
#include "rack.hpp"
#include "view.hpp"


namespace nl {





    class DrumSequencerView: public View {
        private:
            int paramDrawOffset = 0;
            Driver* driver;
            std::vector<rack::Module*> drumSeqModules;

        public:

        

            DrumSequencerView() = default;

            void render(App& app) override;

            void renderDrums(App& app);

            void renderModuleMiniatures(App& app);

        
        };
}
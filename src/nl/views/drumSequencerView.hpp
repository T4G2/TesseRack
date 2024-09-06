#pragma once
#include "rack.hpp"

#include "view.hpp"


namespace nl {





    class DrumSequencerView: public View {
        private:
            int paramDrawOffset = 0;
        public:

        

            DrumSequencerView() = default;

            void renderDrums(Driver& driver, std::vector<rack::Module*> drumSeqModules);


            void renderModuleMiniatures(Driver& driver, std::vector<rack::Module*> drumSeqModules);

        
        };
}
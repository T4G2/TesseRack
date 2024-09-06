# pragma once
#include <map>
#include <vector>

#include "rack.hpp"

#include "views/drumSequencerView.hpp"

namespace nl {

    class App {
    public:

        DrumSequencerView drumSequencerView;
        std::vector<rack::Module*> drumSeqModules = {};

        App() = default;

        void reinit(std::map<rack::Model *, std::vector<rack::Module *>> expanders);
        void reinitDrumSequencers( std::vector<rack::Module *> drumSeqExpanders);
        // ...

        void render(Driver& driver);
    };

} // namespace nl
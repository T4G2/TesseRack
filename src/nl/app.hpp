# pragma once
#include <map>
#include <vector>

#include "rack.hpp"
#include "views/drumSequencerView.hpp"

namespace nl {

    class App {
    public:

        DrumSequencerView drumSequencerView;
        Driver *driver;
        std::vector<rack::Module*> drumSeqModules = {};

        App() = default;

        void reinit(Driver &driverRef, std::map<rack::Model *, std::vector<rack::Module *>> expanders);
        void reinitDrumSequencers( std::vector<rack::Module *> drumSeqExpanders);
        // ...

        // template <typename T: View>
        // void registerView(T view)

        void render();
    };

} // namespace nl
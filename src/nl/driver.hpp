#pragma once

#include <rack.hpp>
#include <array>

#include "color.hpp"
#include "renderer.hpp"

namespace nl {



    class Driver {
        public:
            rack::midi::Input* input;
            rack::midi::Output* output;

            Renderer renderer;

    public:
            Driver() = default;
            Driver(rack::midi::Input* input, rack::midi::Output* output) : input(input), output(output) {
                renderer = Renderer(output);
            };
            
            void initProgrammerMode();
            void disableProgrammerMode();

    };
} // namespace nl
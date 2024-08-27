#pragma once

#include <array>

#include "color.hpp"
#include "colortable.hpp"

#define GRID_SIZE_X 9
#define GRID_SIZE_Y 9
#define GRID_SIZE (GRID_SIZE_X+1) * (GRID_SIZE_Y+1)


namespace nl {

    class Renderer {
        private: 
            std::array<Color, GRID_SIZE> grid = { COLOR_OFF };
            std::vector<uint8_t> dirty = {};
            rack::midi::Output* output;

        public:
        Renderer() = default;
        Renderer(rack::midi::Output* output): output(output) {};

        void setColor(Color color, uint8_t x, uint8_t y);

        void clear();
        void forceClear();
        void flush();
    };
} // namespace nl
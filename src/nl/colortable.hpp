#pragma once

#include "color.hpp"

namespace nl {
#define COLOR_OFF Color::table(0)

    Color convertTableToRGBColor(uint8_t index);
    Color1f convertTableTo1fRangeColor(uint8_t index);
} // namespace nl
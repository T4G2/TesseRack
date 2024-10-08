#include "colortable.hpp"

#include <stdint.h>

#define rgb(r, g, b) {r, g, b},



namespace nl {

    const uint8_t COLORTABLE[128][3] = {
        rgb(97, 97, 97)
        rgb(179, 179, 179)
        rgb(221, 221, 221)
        rgb(255, 255, 255)
        rgb(255, 179, 179)
        rgb(255, 179, 179)
        rgb(221, 97, 97)
        rgb(179, 97, 97)
        rgb(255, 243, 213)
        rgb(255, 179, 97)
        rgb(221, 140, 97)
        rgb(179, 118, 97)
        rgb(255, 238, 161)
        rgb(255, 255, 97)
        rgb(221, 221, 97)
        rgb(179, 179, 97)
        rgb(221, 255, 161)
        rgb(194, 255, 97)
        rgb(161, 221, 97)
        rgb(129, 179, 97)
        rgb(194, 255, 179)
        rgb(97, 255, 97)
        rgb(97, 221, 97)
        rgb(97, 179, 97)
        rgb(194, 255, 194)
        rgb(97, 255, 140)
        rgb(97, 221, 118)
        rgb(97, 179, 107)
        rgb(194, 255, 204)
        rgb(97, 255, 204)
        rgb(97, 221, 161)
        rgb(97, 179, 129)
        rgb(194, 255, 243)
        rgb(97, 255, 233)
        rgb(97, 221, 194)
        rgb(97, 179, 150)
        rgb(194, 243, 255)
        rgb(97, 238, 255)
        rgb(97, 199, 221)
        rgb(97, 161, 179)
        rgb(194, 221, 255)
        rgb(97, 199, 255)
        rgb(97, 161, 221)
        rgb(97, 129, 179)
        rgb(161, 140, 255)
        rgb(97, 97, 255)
        rgb(97, 97, 221)
        rgb(97, 97, 179)
        rgb(204, 179, 255)
        rgb(161, 97, 255)
        rgb(129, 97, 221)
        rgb(118, 97, 179)
        rgb(255, 179, 255)
        rgb(255, 97, 255)
        rgb(221, 97, 221)
        rgb(179, 97, 179)
        rgb(255, 179, 213)
        rgb(255, 97, 194)
        rgb(221, 97, 161)
        rgb(179, 97, 140)
        rgb(255, 118, 97)
        rgb(233, 179, 97)
        rgb(221, 194, 97)
        rgb(161, 161, 97)
        rgb(97, 179, 97)
        rgb(97, 179, 140)
        rgb(97, 140, 213)
        rgb(97, 97, 255)
        rgb(97, 179, 179)
        rgb(140, 97, 243)
        rgb(204, 179, 194)
        rgb(140, 118, 129)
        rgb(255, 97, 97)
        rgb(243, 255, 161)
        rgb(238, 252, 97)
        rgb(204, 255, 97)
        rgb(118, 221, 97)
        rgb(97, 255, 204)
        rgb(97, 233, 255)
        rgb(97, 161, 255)
        rgb(140, 97, 255)
        rgb(204, 97, 252)
        rgb(238, 140, 221)
        rgb(161, 118, 97)
        rgb(255, 161, 97)
        rgb(221, 249, 97)
        rgb(213, 255, 140)
        rgb(97, 255, 97)
        rgb(179, 255, 161)
        rgb(204, 252, 213)
        rgb(179, 255, 246)
        rgb(204, 228, 255)
        rgb(161, 194, 246)
        rgb(213, 194, 249)
        rgb(249, 140, 255)
        rgb(255, 97, 204)
        rgb(255, 194, 97)
        rgb(243, 238, 97)
        rgb(228, 255, 97)
        rgb(221, 204, 97)
        rgb(179, 161, 97)
        rgb(97, 186, 118)
        rgb(118, 194, 140)
        rgb(129, 129, 161)
        rgb(129, 140, 204)
        rgb(204, 170, 129)
        rgb(221, 97, 97)
        rgb(249, 179, 161)
        rgb(249, 186, 118)
        rgb(255, 243, 140)
        rgb(233, 249, 161)
        rgb(213, 238, 118)
        rgb(129, 129, 161)
        rgb(249, 249, 213)
        rgb(221, 252, 228)
        rgb(233, 233, 255)
        rgb(228, 213, 255)
        rgb(179, 179, 179)
        rgb(213, 213, 213)
        rgb(249, 255, 255)
        rgb(233, 97, 97)
        rgb(170, 97, 97)
        rgb(129, 246, 97)
        rgb(97, 179, 97)
        rgb(243, 238, 97)
        rgb(179, 161, 97)
        rgb(238, 194, 97)
        rgb(194, 118, 97)
    };


    Color convertTableToRGBColor(uint8_t index) {
        const uint8_t* colorIn256Range = COLORTABLE[index];
        return Color::RGB(colorIn256Range[0]/2, colorIn256Range[1]/2, colorIn256Range[2]/2);
    }

    Color1f convertTableTo1fRangeColor(uint8_t index) {
        const uint8_t* colorIn256Range = COLORTABLE[index];
        return Color1f{colorIn256Range[0]/255.0f, colorIn256Range[1]/255.0f, colorIn256Range[2]/255.0f};
    }

} // namespace nl
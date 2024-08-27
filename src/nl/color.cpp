#include "color.hpp"



namespace nl {

     Color Color::table(uint8_t color) {
        Color c;
        c.type = LightType::TABLE;
        c.data.table.color = color;
        return c;
    }

    Color Color::flash(uint8_t color1, uint8_t color2) {
        Color c;
        c.type = LightType::FLASHING;
        c.data.flash.color1 = color1;
        c.data.flash.color2 = color2;
        return c;
    }

    Color Color::pulse(uint8_t color1, uint8_t color2) {
        Color c;
        c.type = LightType::PULSING;
        c.data.pulse.color1 = color1;
        c.data.pulse.color2 = color2;
        return c;
    }

    Color Color::RGB(uint8_t color1, uint8_t color2, uint8_t color3) {
        Color c;
        c.type = LightType::RGB;
        c.data.RGB.color1 = color1;
        c.data.RGB.color2 = color2;
        c.data.RGB.color3 = color3;
        return c;
    }

    std::vector<uint8_t> Color::getBytes(uint8_t pos) const {
        switch (type) {
            case LightType::TABLE:
                return {0x0, pos, data.table.color};
            case LightType::FLASHING:
                return {0x1, pos, data.flash.color1, data.flash.color2};
            case LightType::PULSING:
                return {0x2, pos, data.pulse.color1};
            case LightType::RGB:
                return {0x3, pos,data.RGB.color1, data.RGB.color2, data.RGB.color3};
        }

        // will not happen
        return {};
    }

    bool Color::operator==(const Color& other) const {
        if (type != other.type) {
            return false;
        }

        switch (type) {
            case LightType::TABLE:
                return data.table.color == other.data.table.color;
            case LightType::FLASHING:
                return data.flash.color1 == other.data.flash.color1 && data.flash.color2 == other.data.flash.color2;
            case LightType::PULSING:
                return data.pulse.color1 == other.data.pulse.color1 && data.pulse.color2 == other.data.pulse.color2;
            case LightType::RGB:
                return data.RGB.color1 == other.data.RGB.color1 && data.RGB.color2 == other.data.RGB.color2 && data.RGB.color3 == other.data.RGB.color3;
        }

        return false;
    }

} // namespace nl
#pragma once

#include <vector>
#include <cstdint> // For uint8_t


namespace nl {

    enum class LightType {
        TABLE = 0,
        FLASHING = 1,
        PULSING = 2,
        RGB = 3
    };


    struct Color1f {
        float r;
        float g;
        float b;

    };

    class Color {
        public:

            LightType type;
            union {
                struct {
                    uint8_t color;
                } table;
                struct {
                    uint8_t color1;
                    uint8_t color2;
                } flash;
                struct {
                    uint8_t color1;
                    uint8_t color2;
                } pulse;
                struct {
                    uint8_t color1;
                    uint8_t color2;
                    uint8_t color3;
                } RGB;

            } data;

            // Static Constructors
            static Color table(uint8_t color);
            static Color flash(uint8_t color1, uint8_t color2);
            static Color pulse(uint8_t color1, uint8_t color2);
            static Color RGB(uint8_t color1, uint8_t color2, uint8_t color3);

            std::vector<uint8_t> getBytes(uint8_t pos) const;
            bool operator==(const Color& other) const;
    };
} // namespace nl
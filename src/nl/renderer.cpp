#include <rack.hpp>

#include "renderer.hpp"

#define SYSEX_DRAW_MULTIPLE_INQUIRY {240, 0, 32, 41, 2, 13, 3 };


namespace nl {

    void Renderer::setColor(Color color, uint8_t x, uint8_t y) {
        if (x >= GRID_SIZE_X || y >= GRID_SIZE_Y) {
            return;
        }

        uint8_t i = y * (GRID_SIZE_Y + 1) + x;

        if (grid[i] == color) {
            return;
        }
        
        grid[i] = color;
        dirty.push_back(i);
    }

    void Renderer::clear()
    {
        for (uint8_t x = 1; x <= GRID_SIZE_X; x++) {
            for (uint8_t y = 1; y <= GRID_SIZE_Y; y++) {
                setColor(COLOR_OFF, x, y);
            }
        }
    }

    void Renderer::forceClear()
    {
        for (uint8_t x = 1; x <= GRID_SIZE_X; x++) {
            for (uint8_t y = 1; y <= GRID_SIZE_Y; y++) {

                setColor(COLOR_OFF, x, y);
                uint8_t i = y * (GRID_SIZE_Y + 1) + x;
                dirty.push_back(i);
            }
        }

    }

    void Renderer::flush()
    {

        std::vector<uint8_t> msg_bytes = SYSEX_DRAW_MULTIPLE_INQUIRY;

        for (uint8_t i : dirty) {
            Color color = grid[i];
            std::vector<uint8_t> bytes = color.getBytes(i);
            msg_bytes.insert(msg_bytes.end(), bytes.begin(), bytes.end());
        }

        msg_bytes.push_back(247);

        rack::midi::Message msg = rack::midi::Message();
        msg.bytes = msg_bytes;

        INFO("Sending message of size %lld", msg_bytes.size());
        INFO("Message: %s", msg.toString().c_str());

        output->sendMessage(msg);
        dirty.clear();
    }

} // namespace nl
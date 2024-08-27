#include <vector>
#include <cstdint> // For uint8_t

#include "driver.hpp"

#define ENABLE_PROGRAMMER_MODE_BYTES {240, 0, 32, 41, 2, 13, 14, 1, 247};
#define DISABLE_PROGRAMMER_MODE_BYTES {240, 0, 32, 41, 2, 13, 14, 0, 247};

namespace nl {
    void Driver::initProgrammerMode() {
        rack::midi::Message msg = rack::midi::Message();
        msg.bytes = ENABLE_PROGRAMMER_MODE_BYTES;
        output->sendMessage(msg);
    }

    void Driver::disableProgrammerMode() {
        rack::midi::Message msg = rack::midi::Message();
        msg.bytes = DISABLE_PROGRAMMER_MODE_BYTES;
        output->sendMessage(msg);
    }

} // namespace nl
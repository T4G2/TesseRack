#pragma once
#include <rack.hpp>

#include <functional>

enum class ExpansionType {
    MAIN_MODULE,
    DRUM_SEQUENCER,
    NOTE_SEQUENCER,
    CV_SEQUENCER,
};

class ExpansionRegisterMessage {
    ExpansionType moduleType;
    rack::Module* module;
    int position;
};

class ExpansionsUnplugMessage {
    int position;
};

enum class MessageType {
    REGISTER_EXPANSION,
    UNPLUG_EXPANSIONS,
};
class Message {
    MessageType type;
    union {
        ExpansionRegisterMessage* registerMessage;
        ExpansionsUnplugMessage* unplugMessage;
    } message;
};

class MessageSystem {
    public:
        ExpansionType moduleType;
        rack::Module* module;
        MessageSystem() = default;
        MessageSystem(ExpansionType moduleType, rack::Module* module);

        void onExpanderConfigurationChange();
        MessageSystem* getLeftMessageSystem();
        MessageSystem* getRightMessageSystem();

        static MessageSystem* getMessageSystemFromModule (rack::Module* module);
};
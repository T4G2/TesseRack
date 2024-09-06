// #include "expansion.hpp"

// #include "plugin.hpp"


// struct NLMmk3 : Module {
//     void onExpanderConfigurationChange();
// }


// MessageSystem::MessageSystem(ExpansionType moduleType, rack::Module* module):
//     moduleType(moduleType),
//     module(module) {}

// void MessageSystem::onExpanderConfigurationChange() {
//     switch (moduleType) {
//         case ExpansionType::MAIN_MODULE:
//             dynamic_cast<NLMmk3*>(module)->onExpanderConfigurationChange();
//             break;
//         case ExpansionType::DRUM_SEQUENCER:
//         case ExpansionType::NOTE_SEQUENCER:
//         case ExpansionType::CV_SEQUENCER:
//             MessageSystem* leftMessageSystem = getLeftMessageSystem();
//             if (leftMessageSystem) {
//                 leftMessageSystem->onExpanderConfigurationChange();
//             }
//     }
// }

//     MessageSystem* MessageSystem::getLeftMessageSystem() {
//         rack::Module* leftModule = module->getLeftExpander().module;
//         if (!leftModule) {
//             return nullptr;
//         }
//         return getMessageSystemFromModule(leftModule);
//     }

//     MessageSystem* MessageSystem::getRightMessageSystem() {
//         rack::Module* rightModule = module->getRightExpander().module;
//         if (!rightModule) {
//             return nullptr;
//         }
//         return getMessageSystemFromModule(rightModule);
//     }

//     MessageSystem* MessageSystem::getMessageSystemFromModule (rack::Module* module) {
//        if( module->model == modelNLMmk3 ) {
//                 return &(dynamic_cast<NLMmk3*>(module)->messageSystem);
//         else if (leftModule->model == modelNLMmk3_DrumSequencerExpander) {
//                 return &(dynamic_cast<NLMmk3_DrumSequencerExpander*>(module)->messageSystem);
//         }

//         return nullptr;
//     }


    
// }

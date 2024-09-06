#include "plugin.hpp"


rack::Plugin* pluginInstance;

// extern Model* modelNovaPad;

extern rack::Model* modelTemplate;

void init(Plugin* p) {
	pluginInstance = p;

	// Add modules here
	// p->addModel(modelMyModule);
	// p->addModel(modelTemplate);
	p->addModel(modelNLMmk3);
	p->addModel(modelNLMmk3_DrumSequencerExpander);

	// Any other plugin initialization may go here.
	// As an alternative, consider lazy-loading assets and lookup tables when your module is created to reduce startup times of Rack.
}

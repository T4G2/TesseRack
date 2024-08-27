#include "plugin.hpp"


Plugin* pluginInstance;

// extern Model* modelNovaPad;

extern Model* modelTemplate;

void init(Plugin* p) {
	pluginInstance = p;

	// Add modules here
	// p->addModel(modelMyModule);
	// p->addModel(modelTemplate);
	p->addModel(modelNLMmk3);
	// Any other plugin initialization may go here.
	// As an alternative, consider lazy-loading assets and lookup tables when your module is created to reduce startup times of Rack.
}

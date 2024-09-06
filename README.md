```sh
#open in MinGW shell

~/RackSDK/helper.py createmodule Template res/TemplateExport.svg src/Template.cpp


~/RackSDK/helper.py createmodule NLMmk3 res/NLMmk3.svg src/TNLMmk3.cpp
~/RackSDK/helper.py createmodule NLMmk3_DrumSequencerExpander res/NLMmk3_DrumSequencerExpander.svg src/NLMmk3_DrumSequencerExpander.cpp


make

make dist

make install
```


## Roadmap

- [x] 27.8 Rendering
- [ ] Input
- [ ] Drum Sequencer Expander
- [ ] Sequencer Expander
- [ ] Song Structure Expander

#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "MidiDevicesTableComponent.h"

class MidiDevicesComponent : public juce::Component {
public:
    MidiDevicesComponent();
    ~MidiDevicesComponent() override = default;

    void resized() override;

private:

    juce::Label inputLabel, outputLabel;
    std::unique_ptr<MidiDevicesTableComponent> inputTable, outputTable;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiDevicesComponent)
};

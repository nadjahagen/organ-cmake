#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_devices/juce_audio_devices.h>

class MainComponent : public juce::Component
{
public:
    MainComponent();
    ~MainComponent() override = default;
    void resized() override;

private:
    std::unique_ptr<juce::TabbedComponent> tabbedComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

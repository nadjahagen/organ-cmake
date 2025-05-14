#include "MainComponent.h"

#include "midi/MidiDevicesComponent.h"

MainComponent::MainComponent()
{
    tabbedComponent = std::make_unique<juce::TabbedComponent>(juce::TabbedButtonBar::TabsAtTop);
    addAndMakeVisible(*tabbedComponent);

    tabbedComponent->addTab("MIDI Devices", juce::Colours::white, new MidiDevicesComponent(), true);
    tabbedComponent->addTab("Audio", juce::Colours::white, new Component(), true);
    tabbedComponent->addTab("Presets", juce::Colours::white, new Component(), true);
    tabbedComponent->addTab("Stops", juce::Colours::white, new Component(), true);

    setSize(800, 600);
}

void MainComponent::resized()
{
    tabbedComponent->setBounds(getLocalBounds());
}

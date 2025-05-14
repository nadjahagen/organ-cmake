#include "MidiDevicesComponent.h"
#include <juce_audio_devices/juce_audio_devices.h>

MidiDevicesComponent::MidiDevicesComponent()
{
    inputLabel.setText("Detected MIDI Input Devices:", juce::dontSendNotification);
    inputLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    addAndMakeVisible(inputLabel);

    inputTable = std::make_unique<MidiDevicesTableComponent>(MidiDeviceType::Input);
    addAndMakeVisible(*inputTable);

    outputLabel.setText("Detected MIDI Output Devices:", juce::dontSendNotification);
    outputLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    addAndMakeVisible(outputLabel);

    outputTable = std::make_unique<MidiDevicesTableComponent>(MidiDeviceType::Output);
    addAndMakeVisible(*outputTable);
}

void MidiDevicesComponent::resized()
{
    auto area = getLocalBounds().reduced(10);

    inputLabel.setBounds(area.removeFromTop(20));
    inputTable->setBounds(area.removeFromTop(150));

    area.removeFromTop(10);

    outputLabel.setBounds(area.removeFromTop(20));
    outputTable->setBounds(area.removeFromTop(150));
}



#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_devices/juce_audio_devices.h>

enum class MidiDeviceType { Input, Output };

class MidiDevicesTableComponent final : public juce::Component,
                                        public juce::TableListBoxModel
{
public:
    explicit MidiDevicesTableComponent(MidiDeviceType type);
    ~MidiDevicesTableComponent() override = default;

    int getNumRows() override;
    void paintRowBackground(juce::Graphics&, int rowNumber, int width, int height, bool rowIsSelected) override;
    void paintCell(juce::Graphics&, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
    Component* refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, juce::Component* existingComponentToUpdate) override;
    void resized() override;

private:
    MidiDeviceType deviceType;
    std::unique_ptr<juce::LookAndFeel> headerLookAndFeel;

    struct MidiDevice
    {
        bool active = false;
        juce::String name;
    };

    juce::TableListBox table { {}, this };
    juce::Font font { 14.0f };
    juce::Array<MidiDevice> deviceList;

    void loadDevices();

    //==============================================================================
    class SelectionColumnCustomComponent : public Component
    {
    public:
        explicit SelectionColumnCustomComponent(MidiDevicesTableComponent& ownerRef);
        void resized() override;
        void setRowAndColumn(int newRow, int newColumn);

    private:
        MidiDevicesTableComponent& owner;
        juce::ToggleButton toggleButton;
        int row = -1;
    };

    //==============================================================================
    class NoHoverHeaderLookAndFeel : public juce::LookAndFeel_V4
    {
    public:
        NoHoverHeaderLookAndFeel();
        void drawTableHeaderColumn (juce::Graphics& g, juce::TableHeaderComponent& header,
                            const juce::String& columnName, int columnId, int width, int height,
                            bool isMouseOver, bool isMouseDown, int columnIndex) override;
    };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MidiDevicesTableComponent)
};

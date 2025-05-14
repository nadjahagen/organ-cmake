#include "MidiDevicesTableComponent.h"

MidiDevicesTableComponent::MidiDevicesTableComponent(MidiDeviceType type)
    : deviceType(type)
{
    loadDevices();

    addAndMakeVisible(table);

    table.setColour(juce::ListBox::outlineColourId, juce::Colours::grey);
    table.setColour(juce::ListBox::backgroundColourId, juce::Colours::white);
    table.setOutlineThickness(1);

    headerLookAndFeel = std::make_unique<NoHoverHeaderLookAndFeel>();
    table.getHeader().setLookAndFeel(headerLookAndFeel.get());

    table.getHeader().addColumn("Active", 0, 60);
    table.getHeader().addColumn("Device Name", 1, 300);
    table.getHeader().setStretchToFitActive(true);

    table.setMultipleSelectionEnabled(false);
    table.setClickingTogglesRowSelection(false);
}

int MidiDevicesTableComponent::getNumRows()
{
    return deviceList.size();
}

void MidiDevicesTableComponent::paintRowBackground(juce::Graphics& g, int rowNumber, int /*width*/, int /*height*/, bool /*rowIsSelected*/)
{
    if (rowNumber % 2 == 0)
        g.fillAll(juce::Colours::white);
    else
        g.fillAll(juce::Colours::whitesmoke);
}

void MidiDevicesTableComponent::paintCell(juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    g.setColour(juce::Colours::black);
    g.setFont(font);

    if (rowNumber < deviceList.size())
    {
        const auto& device = deviceList[rowNumber];
        juce::String text;

        if (columnId == 1)
        {
            text = device.name;
        }
        g.drawText(text, 2, 0, width - 4, height, juce::Justification::centredLeft);
    }
    g.fillRect(width - 1, 0, 1, height);
}

juce::Component* MidiDevicesTableComponent::refreshComponentForCell(int rowNumber, int columnId, bool /*isRowSelected*/, juce::Component* existingComponentToUpdate)
{
    if (columnId == 0)
    {
        auto* selectionBox = dynamic_cast<SelectionColumnCustomComponent*> (existingComponentToUpdate);
        if (selectionBox == nullptr)
            selectionBox = new SelectionColumnCustomComponent(*this);

        selectionBox->setRowAndColumn(rowNumber, columnId);
        return selectionBox;
    }

    jassert(existingComponentToUpdate == nullptr);
    return nullptr;
}

void MidiDevicesTableComponent::resized()
{
    table.setBoundsInset(juce::BorderSize<int>(8));
}

void MidiDevicesTableComponent::loadDevices()
{
    deviceList.clear();
    if (deviceType == MidiDeviceType::Input)
    {
        for (const auto& device : juce::MidiInput::getAvailableDevices())
            deviceList.add({ false, device.name });
    }
    else
    {
        for (const auto& device : juce::MidiOutput::getAvailableDevices())
            deviceList.add({ false, device.name });
    }
    table.updateContent();
}

//==============================================================================
// SelectionColumnCustomComponent

MidiDevicesTableComponent::SelectionColumnCustomComponent::SelectionColumnCustomComponent(MidiDevicesTableComponent& ownerRef)
    : owner(ownerRef)
{
    toggleButton.setColour(juce::ToggleButton::tickColourId, juce::Colours::black);
    toggleButton.setColour(juce::ToggleButton::textColourId, juce::Colours::black);
    toggleButton.setColour(juce::ToggleButton::tickDisabledColourId, juce::Colours::black);

    addAndMakeVisible(toggleButton);
    toggleButton.onClick = [this] {
        if (row >= 0 && row < owner.deviceList.size())
            owner.deviceList.getReference(row).active = toggleButton.getToggleState();
    };
}

void MidiDevicesTableComponent::SelectionColumnCustomComponent::resized()
{
    toggleButton.setBoundsInset(juce::BorderSize<int>(2));
}

void MidiDevicesTableComponent::SelectionColumnCustomComponent::setRowAndColumn(int newRow, int /*newColumn*/)
{
    row = newRow;
    if (row >= 0 && row < owner.deviceList.size())
    {
        toggleButton.setToggleState(owner.deviceList[row].active, juce::dontSendNotification);
    }
}

//==============================================================================
// NoHoverHeaderLookAndFeel

MidiDevicesTableComponent::NoHoverHeaderLookAndFeel::NoHoverHeaderLookAndFeel() {}

void MidiDevicesTableComponent::NoHoverHeaderLookAndFeel::drawTableHeaderColumn (juce::Graphics& g, juce::TableHeaderComponent& header,
                            const juce::String& columnName, int columnId, int width, int height,
                            bool isMouseOver, bool isMouseDown, int columnIndex)
{
    // Override this to prevent the column header from changing color on hover
    g.fillAll (juce::Colours::white); // Keep the background white on hover
    g.setColour(juce::Colours::black);
    g.setFont(juce::Font(14.0f));
    g.drawText(columnName, 5, 0, width - 10, height, juce::Justification::centredLeft);

    g.setColour(juce::Colours::grey);
    g.drawLine(0.0f, static_cast<float>(height - 1), static_cast<float>(width), static_cast<float>(height - 1), 1.0f);
}

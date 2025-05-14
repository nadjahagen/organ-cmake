#include "gui/MainComponent.h"

class MainWindow : public juce::DocumentWindow {
public:
    MainWindow(): DocumentWindow("Hybrid Organ",
        juce::Colours::white,
        allButtons)
    {
        setUsingNativeTitleBar(true);
        setContentOwned(new MainComponent(), true);

        setResizable(true, true);
        centreWithSize(getWidth(), getHeight());
        Component::setVisible(true);
    }

    void closeButtonPressed() override
    {
        juce::JUCEApplication::getInstance()->systemRequestedQuit();
    }
};

class HybridOrganApplication : public juce::JUCEApplication {
public:
    const juce::String getApplicationName() override       { return "Hybrid Organ"; }
    const juce::String getApplicationVersion() override    { return "1.0"; }

    void initialise(const juce::String&) override{
        mainWindow = std::make_unique<MainWindow>();
    }

    void shutdown() override{
        mainWindow = nullptr;
    }

private:
    std::unique_ptr<MainWindow> mainWindow;
};

START_JUCE_APPLICATION(HybridOrganApplication)

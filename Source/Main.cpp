#include <JuceHeader.h>
#include "MainComponent.h"
//Menna Tullah Mahmoud 20242351
//task 3, 6, 9 + Bonus(Dynamic Mood Theme)
/*I added a feature called Dynamic Mood Theme, which automatically changes the player’s background color based on the song’s speed
when the music is fast, the UI turns cool and energetic; when it’s slow, it becomes warm and calm”*/

// Our application class
class SimpleAudioPlayer : public juce::JUCEApplication
{
public:
    const juce::String getApplicationName() override { return "Simple Audio Player"; }
    const juce::String getApplicationVersion() override { return "1.0"; }

    void initialise(const juce::String&) override
    {
        // Create and show the main window
        mainWindow = std::make_unique<MainWindow>(getApplicationName());
    }

    void shutdown() override
    {
        mainWindow = nullptr; // Clean up
    }

private:
    // The main window of the app
    class MainWindow : public juce::DocumentWindow
    {
    public:
        MainWindow(juce::String name)
            : DocumentWindow(name,
                juce::Colours::lightgrey,
                DocumentWindow::allButtons)
        {
            setUsingNativeTitleBar(true);
            setContentOwned(new MainComponent(), true); // MainComponent = our UI + logic
            centreWithSize(400, 200);
            setVisible(true);
        }

        void closeButtonPressed() override
        {
            juce::JUCEApplication::getInstance()->systemRequestedQuit();
        }
    };

    std::unique_ptr<MainWindow> mainWindow;
};

// This macro starts the app
START_JUCE_APPLICATION(SimpleAudioPlayer)
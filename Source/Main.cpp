/*
Document Link: https://drive.google.com/file/d/1hmnmzOvaO6E9ZsnZCDQA7pkFc5EolQwi/view?usp=sharing
Video Link: https://drive.google.com/file/d/1ddSHwqhR4VjjJ47KGZJn-3ecHfgJaYLY/view?usp=sharing
Repo Link: https://github.com/mennamahmoud007/CS213_A2_Section-S33-34-20242351-20240276-20242394

CS213_A2_Section-S33/34
Shrouk Hani — ID: 20240276 — Tasks: 2, 5, 8 + Bonus 1 (Multiple players) + Bonus 2 (Remove Button) + Bonus 3 (Clear Button)
Menna Tullah Mahmoud — ID: 20242351 — Tasks: 3, 6, 9 + Bonus 1 (task 13) + Bonus 2 (Dynamic Mood Theme) + Bonus 3 (Gentle Stop)
Yasmin Sherif — ID: 20242394 — Tasks: 4, 7, 10 + Bonus 1 (task 12) + Bonus 2 (Mixer) 
 */

#include <JuceHeader.h>
#include "MainComponent.h"
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
            centreWithSize(1280, 760);
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
#pragma once						
#include <JuceHeader.h>
#include "PlayerAudio.h"

class PlayerGUI : public juce::Component,
    public juce::Button::Listener,
    public juce::Slider::Listener,
    public juce::Timer

{
public:
    PlayerGUI();
    ~PlayerGUI() override;

    void paint(juce::Graphics& g) override;
    void resized() override;
    void PlayerGUI::timerCallback() override;
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);
    void releaseResources();
    //Bonus 2(task 13)
    void loadSession();
    void saveSession();

private:
    PlayerAudio playerAudio;

    // GUI elements
    juce::TextButton loadButton{ "Load File" };
    juce::TextButton restartButton{ "Restart" };
    juce::TextButton stopButton{ "Stop" };
    juce::Slider volumeSlider;

    juce::TextButton muteButton{ "Mute" }; //task 3
    juce::Slider speedSlider;   //task 6
    //task 9
    double progressValue = 0.0; 
    juce::ProgressBar progressBar{ progressValue };
    juce::Timer* timer = nullptr; 
    juce::Label timeLabel;

    juce::Colour currentBackground{ juce::Colours::darkgrey };//Bonus 1 (Dynamic Mood Theme)


    std::unique_ptr<juce::FileChooser> fileChooser;

    // Event handlers
    void buttonClicked(juce::Button* button) override;
    void sliderValueChanged(juce::Slider* slider) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerGUI)
};

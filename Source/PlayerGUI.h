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

    void timerCallback() override;
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);
    void releaseResources();
    void loadSession();
    void saveSession();
    void sliderDragStarted(juce::Slider* slider) override;
    void sliderDragEnded(juce::Slider* slider) override;

private:
    PlayerAudio playerAudio;

    // GUI elements
    juce::TextButton loadButton{ "Load File" };
    juce::TextButton restartButton{ "Restart" };
    juce::TextButton stopButton{ "Stop" };
    juce::TextButton playButton{ "Play " };
    juce::TextButton pauseButton{ "Pause " };
    juce::TextButton startButton{ "Start" };
    juce::TextButton endButton{ "End" };
    juce::TextButton muteButton{ "Mute" };
    juce::TextButton loopButton{ "Loop" };
    juce::TextButton setA{ "Marker A" };
    juce::TextButton setB{ "Marker B" };
    juce::TextButton jumpBack{ "-10s" };
    juce::TextButton jumpForward{ "+10s" };

    juce::Slider positionSlider;
    juce::Slider speedSlider;   
    juce::Slider volumeSlider;
    juce::ProgressBar progressBar{ progressValue };
    juce::Label timeLabel;
    juce::Colour currentBackground{ juce::Colours::darkgrey };

    void updatePositionSlider(); // task 7
    void updateProgressBar();    // task 9

    bool isLooping = false;
    const double jump = 10.0;

    double progressValue = 0.0;
    bool isDragging = false;


    std::unique_ptr<juce::FileChooser> fileChooser;

    // Event handlers
    void buttonClicked(juce::Button* button) override;
    void sliderValueChanged(juce::Slider* slider) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerGUI)
};
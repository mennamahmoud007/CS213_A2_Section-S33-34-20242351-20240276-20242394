#pragma once						
#include <JuceHeader.h>
#include "PlayerAudio.h"

class PlayerGUI : public juce::Component,
    public juce::Button::Listener,
    public juce::Slider::Listener,
    public juce::Timer,
    public juce::ListBoxModel
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

    void addFilesToPlaylist(int trackNumber);
    void loadAndPlayFile(const juce::File& file, int trackNumber);
    void updateMetadataDisplay(const juce::File& file, int trackNumber);
    void removeSelected(int trackNumber);
    void clearPlaylist(int trackNumber);

    int getNumRows() override;
    int getNumRows2() ;
    void paintListBoxItem(int row, juce::Graphics& g, int width, int height, bool selected) override;
    void paintListBoxItem2(int row, juce::Graphics& g, int width, int height, bool selected) ;
    void selectedRowsChanged(int lastRow) override;
    void selectedRowsChanged2(int lastRow);

private:
    PlayerAudio playerAudio;
    PlayerAudio playerAudio2;

    // GUI elements
    juce::TextButton loadButton{ "Load File" };
    juce::TextButton restartButton{ "Restart" };
    juce::TextButton stopButton{ "Stop" };
    juce::TextButton playButton{ "Play " };
    juce::TextButton pauseButton{ "Pause " };
    juce::TextButton startButton{ "Start" };
    juce::TextButton endButton{ "End" };
    juce::TextButton nextButton{ "Next" };
    juce::TextButton prevButton{ "Prev" };
    juce::TextButton muteButton{ "Mute" };
    juce::TextButton loopButton{ "Loop" };
    juce::TextButton setA{ "Marker A" };
    juce::TextButton setB{ "Marker B" };
    juce::TextButton removeButton{ "Remove" };
    juce::TextButton clearButton{ "Clear" };
    juce::TextButton jumpBack{ "-10s" };
    juce::TextButton jumpForward{ "+10s" };

    juce::TextButton loadButton2{ "Load File" };
    juce::TextButton restartButton2{ "Restart" };
    juce::TextButton stopButton2{ "Stop" };
    juce::TextButton playButton2{ "Play " };
    juce::TextButton pauseButton2{ "Pause " };
    juce::TextButton startButton2{ "Start" };
    juce::TextButton endButton2{ "End" };
    juce::TextButton nextButton2{ "Next" };
    juce::TextButton prevButton2{ "Prev" };
    juce::TextButton muteButton2{ "Mute" };
    juce::TextButton loopButton2{ "Loop" };
    juce::TextButton setA2{ "Marker A" };
    juce::TextButton setB2{ "Marker B" };
    juce::TextButton removeButton2{ "Remove" };
    juce::TextButton clearButton2{ "Clear" };
    juce::TextButton jumpBack2{ "-10s" };
    juce::TextButton jumpForward2{ "+10s" };

    juce::Slider positionSlider;
    juce::Slider positionSlider2;

    juce::Slider speedSlider;   
    juce::Slider speedSlider2;

    juce::Slider volumeSlider;
    juce::Slider volumeSlider2;

    juce::ProgressBar progressBar{ progressValue };
    juce::ProgressBar progressBar2{ progressValue2 };

    juce::Label timeLabel;
    juce::Label timeLabel2;

    juce::Label metadataLabel1;
    juce::Label metadataLabel2;

    juce::Colour currentBackground{ juce::Colours::darkgrey };
    juce::Colour currentBackground2{ juce::Colours::darkgrey };

    void updatePositionSlider(); // task 7
    void updateProgressBar();    // task 9

    bool isLooping = false;
    bool isLooping2 = false;
    const double jump = 10.0;

    double progressValue = 0.0;
    double progressValue2 = 0.0;
    bool isDragging = false;
    bool isDragging2 = false;

    juce::ListBox playlistBox1;
    juce::ListBox playlistBox2;

    juce::Array<juce::File> playlist1;
    juce::Array<juce::File> playlist2;

    juce::StringArray playlistFiles1;
    juce::StringArray playlistFiles2;

    int currentIndex1 = -1;
    int currentIndex2 = -1;

    std::unique_ptr<juce::FileChooser> fileChooser;

    // Event handlers
    void buttonClicked(juce::Button* button) override;
    void sliderValueChanged(juce::Slider* slider) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerGUI)
};
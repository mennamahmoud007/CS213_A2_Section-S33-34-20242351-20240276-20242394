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

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);
    void releaseResources();
    void timerCallback() override;
    void sliderDragStarted(juce::Slider* slider) override;
    void sliderDragEnded(juce::Slider* slider) override;
    void sliderValueChanged(juce::Slider* slider) override;
    void buttonClicked(juce::Button* button) override;

    int getNumRows() override;
    void paintListBoxItem(int row, juce::Graphics& g, int width, int height, bool selected) override;
    void selectedRowsChanged(int lastRow) override;

private:
    PlayerAudio playerAudio1;
    PlayerAudio playerAudio2;

    juce::TextButton loadButton1{ "Load" };
    juce::TextButton playButton1{ "Play" };
    juce::TextButton pauseButton1{ "Pause" };
    juce::TextButton stopButton1{ "Stop" };
    juce::TextButton nextButton1{ "Next" };
    juce::TextButton prevButton1{ "Prev" };
    juce::TextButton loopButton1{ "Loop" };
    juce::TextButton removeButton1{ "Remove" };
    juce::TextButton clearButton1{ "Clear" };

    juce::TextButton loadButton2{ "Load" };
    juce::TextButton playButton2{ "Play" };
    juce::TextButton pauseButton2{ "Pause" };
    juce::TextButton stopButton2{ "Stop" };
    juce::TextButton nextButton2{ "Next" };
    juce::TextButton prevButton2{ "Prev" };
    juce::TextButton loopButton2{ "Loop" };
    juce::TextButton removeButton2{ "Remove" };
    juce::TextButton clearButton2{ "Clear" };

    juce::Slider volumeSlider1;
    juce::Slider volumeSlider2;
    juce::Slider positionSlider1;
    juce::Slider positionSlider2;

    juce::Label timeLabel1;
    juce::Label timeLabel2;
    juce::Label metadataLabel1;
    juce::Label metadataLabel2;

    bool isDragging1 = false;
    bool isDragging2 = false;
    bool isLooping1 = false;
    bool isLooping2 = false;

    juce::ListBox playlistBox1;
    juce::ListBox playlistBox2;
    juce::Array<juce::File> playlist1;
    juce::Array<juce::File> playlist2;
    juce::StringArray playlistFiles1;
    juce::StringArray playlistFiles2;
    int currentIndex1 = -1;
    int currentIndex2 = -1;

    std::unique_ptr<juce::FileChooser> fileChooser;

    void addFilesToPlaylist(int trackNumber);
    void loadAndPlayFile(const juce::File& file, int trackNumber);
    void updateMetadataDisplay(const juce::File& file, int trackNumber);
    void removeSelected(int trackNumber);
    void clearPlaylist(int trackNumber);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerGUI)
};

#include "PlayerGUI.h"
#include "tag.h"
#include "fileref.h"
#include "tagunion.h"
#include "tagutils.h"
PlayerGUI::PlayerGUI()
{
<<<<<<< Updated upstream
    // Add buttons
    for (auto* btn : { &loadButton, &restartButton , &stopButton })
=======
    for (auto* btn : { &loadButton, &restartButton, &stopButton, &muteButton, &playButton, &pauseButton, &startButton, &endButton, &loopButton })
>>>>>>> Stashed changes
    {
        btn->addListener(this);
        addAndMakeVisible(btn);
    }

    volumeSlider.setRange(0.0, 1.0, 0.01);
    volumeSlider.setValue(0.5);
    volumeSlider.addListener(this);
    addAndMakeVisible(volumeSlider);

<<<<<<< Updated upstream
=======
    positionSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    positionSlider.addListener(this);
    addAndMakeVisible(positionSlider);

    timeLabel.setText("00:00 / 00:00", juce::dontSendNotification);
    timeLabel.setJustificationType(juce::Justification::centred);
    timeLabel.setFont(juce::Font(15.0f, juce::Font::bold));
    addAndMakeVisible(timeLabel);

    addAndMakeVisible(metadataLabel);
    metadataLabel.setText("No file loaded", juce::dontSendNotification);
    metadataLabel.setJustificationType(juce::Justification::centredLeft);
    metadataLabel.setColour(juce::Label::backgroundColourId, juce::Colours::lightgrey);
    metadataLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    metadataLabel.setFont(juce::Font(16.0f, juce::Font::bold));

    startTimer(100);
>>>>>>> Stashed changes
}

PlayerGUI::~PlayerGUI() {}

void PlayerGUI::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkgrey);
}

void PlayerGUI::resized()
{
    int y = 20;
    loadButton.setBounds(20, y, 100, 40);
    restartButton.setBounds(140, y, 80, 40);
    stopButton.setBounds(240, y, 80, 40);
    playButton.setBounds(340, y, 80, 40);
    pauseButton.setBounds(440, y, 80, 40);
    startButton.setBounds(540, y, 80, 40);
    endButton.setBounds(640, y, 80, 40);
    muteButton.setBounds(740, y, 80, 40);
    loopButton.setBounds(840, y, 80, 40);

    volumeSlider.setBounds(20, 100, getWidth() - 40, 30);
    positionSlider.setBounds(120, 140, getWidth() - 160, 30);

    int labelHeight = 20;
    timeLabel.setBounds(20, positionSlider.getY() + 5, 100, labelHeight);
    metadataLabel.setBounds(20, 180, getWidth() - 40, 40);
}

void PlayerGUI::buttonClicked(juce::Button* button)
{
    if (button == &loadButton)
    {
        fileChooser = std::make_unique<juce::FileChooser>("Select an audio file...", juce::File{}, "*.wav;*.mp3");

        fileChooser->launchAsync(juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles,
            [this](const juce::FileChooser& fc)
            {
                auto file = fc.getResult();
                if (file.existsAsFile())
                {
                    playerAudio.LoadFile(file);
                    updateMetadataDisplay(file);
                }
            });
    }

    if (button == &restartButton)
        playerAudio.start();
    if (button == &stopButton)
    {
        playerAudio.stop();
        playerAudio.setPosition(0.0);
    }
    if (button == &playButton)
        playerAudio.start();
    if (button == &pauseButton)
        playerAudio.stop();
    if (button == &startButton)
        playerAudio.setPosition(0.0);
    if (button == &endButton)
        playerAudio.goToEnd();
    if (button == &muteButton)
    {
        bool state = !playerAudio.ismuted();
        playerAudio.setmute(state);
        muteButton.setButtonText(state ? "unMute" : "Mute");
    }
    if (button == &loopButton)
    {
        isLooping = !isLooping;
        playerAudio.setLooping(isLooping);
        loopButton.setButtonText(isLooping ? "UnLoop" : "Loop");
    }
}

void PlayerGUI::updateMetadataDisplay(const juce::File& file)
{
    if (!file.existsAsFile())
        return;

    taglib::FileRef f(file.getFullPathName().toRawUTF8());
    juce::String text;

    if (!f.isNull() && f.tag())
    {
        taglib::Tag* tag = f.tag();
        juce::String title = tag->title().toCString(true);
        juce::String artist = tag->artist().toCString(true);
        juce::String album = tag->album().toCString(true);
        double duration = playerAudio.getLength();

        if (title.isNotEmpty() || artist.isNotEmpty() || album.isNotEmpty())
            text = "Title: " + title + ", Artist: " + artist + ", Album: " + album
            + ", Duration: " + juce::String(duration, 2) + " s";
        else
            text = "Filename: " + file.getFileName();
    }
    else
        text = "Filename: " + file.getFileName();

    metadataLabel.setText(text, juce::dontSendNotification);
}

void PlayerGUI::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &volumeSlider)
        playerAudio.setGain((float)slider->getValue());
}

void PlayerGUI::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    playerAudio.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void PlayerGUI::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    playerAudio.getNextAudioBlock(bufferToFill);
}

void PlayerGUI::releaseResources()
{
    playerAudio.releaseResources();
}

<<<<<<< Updated upstream

void PlayerGUI::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkgrey);
}

void PlayerGUI::resized()
{
    int y = 20;
    loadButton.setBounds(20, y, 100, 40);
    restartButton.setBounds(140, y, 80, 40);
    stopButton.setBounds(240, y, 80, 40);
    /*prevButton.setBounds(340, y, 80, 40);
    nextButton.setBounds(440, y, 80, 40);*/

    volumeSlider.setBounds(20, 100, getWidth() - 40, 30);
}

void PlayerGUI::buttonClicked(juce::Button* button)
{
    if (button == &loadButton)
    {
        juce::FileChooser chooser("Select audio files...",
            juce::File{},
            "*.wav;*.mp3");

        fileChooser = std::make_unique<juce::FileChooser>(
            "Select an audio file...",
            juce::File{},
            "*.wav;*.mp3");

        fileChooser->launchAsync(
            juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles,
            [this](const juce::FileChooser& fc)
            {
                auto file = fc.getResult();
                if (file.existsAsFile())
                {
                    playerAudio.LoadFile(file);
                }
            });
    }

    if (button == &restartButton)
    {
        playerAudio.start();
    }

    if (button == &stopButton)
    {
        playerAudio.stop();
        playerAudio.setPosition(0.0);
    }

}

void PlayerGUI::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &volumeSlider)
        playerAudio.setGain((float)slider->getValue());
}
=======
void PlayerGUI::timerCallback()
{
    if (!isDragging)
    {
        double currentPosition = playerAudio.getPosition();
        double totalLength = playerAudio.getLength();

        positionSlider.setRange(0.0, totalLength, 0.01);
        positionSlider.setValue(currentPosition, juce::dontSendNotification);

        int currentInt = static_cast<int>(currentPosition);
        int totalInt = static_cast<int>(totalLength);

        int currentMinutes = currentInt / 60;
        int currentSeconds = currentInt % 60;
        int totalMinutes = totalInt / 60;
        int totalSeconds = totalInt % 60;

        juce::String time = juce::String::formatted("%02d:%02d / %02d:%02d",
            currentMinutes, currentSeconds, totalMinutes, totalSeconds);

        timeLabel.setText(time, juce::dontSendNotification);
    }
}

void PlayerGUI::sliderDragStarted(juce::Slider* slider)
{
    if (slider == &positionSlider)
        isDragging = true;
}

void PlayerGUI::sliderDragEnded(juce::Slider* slider)
{
    if (slider == &positionSlider)
    {
        isDragging = false;
        playerAudio.setPosition(positionSlider.getValue());
    }
}
>>>>>>> Stashed changes

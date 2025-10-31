#include "PlayerGUI.h"

PlayerGUI::PlayerGUI()
{
    // Add buttons
    for (auto* btn : { &loadButton, &restartButton , &stopButton, &muteButton })
    {
        btn->addListener(this);
        addAndMakeVisible(btn);
    }

    // Volume slider
    volumeSlider.setRange(0.0, 1.0, 0.01);
    volumeSlider.setValue(0.5);
    volumeSlider.addListener(this);
    addAndMakeVisible(volumeSlider);

    addAndMakeVisible(progressBar);
    startTimerHz(30); 

    // time label (show current / total)
    timeLabel.setText("0:00 / 0:00", juce::dontSendNotification);
    timeLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    timeLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(timeLabel);

    speedSlider.setRange(0.25, 2.0, 0.25);
    speedSlider.setValue(1.0);
    speedSlider.addListener(this);
    addAndMakeVisible(speedSlider);
    speedSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 50, 20);


}

PlayerGUI::~PlayerGUI() {}


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


void PlayerGUI::paint(juce::Graphics& g)
{
    g.fillAll(currentBackground);
}

void PlayerGUI::resized()
{
    int y = 20;
    loadButton.setBounds(20, y, 100, 40);
    restartButton.setBounds(140, y, 80, 40);
    stopButton.setBounds(240, y, 80, 40);
    muteButton.setBounds(340, y,80,40);


    volumeSlider.setBounds(20, 100, getWidth() - 40, 30);
    speedSlider.setBounds(20, 150, getWidth() - 40, 30);
    progressBar.setBounds(20, 200, getWidth() - 40, 20);
    timeLabel.setBounds(20, 175, getWidth() - 40, 20);


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

    if (button == &muteButton)
    {
        bool state = !playerAudio.ismuted();
        playerAudio.setmute(state);
        muteButton.setButtonText(state ? "unMute": "Mute");
    }

}

void PlayerGUI::timerCallback()
{
    double pos = playerAudio.getPosition();
    double len = playerAudio.getLength();

    if (len > 0)
        progressValue = pos / len;
    else
        progressValue = 0.0;

    int currentSec = (int)pos;
    int totalSec = (int)len;

    juce::String currentTime = juce::String(currentSec / 60).paddedLeft('0', 2)
        + ":" + juce::String(currentSec % 60).paddedLeft('0', 2);
    juce::String totalTime = juce::String(totalSec / 60).paddedLeft('0', 2)
        + ":" + juce::String(totalSec % 60).paddedLeft('0', 2);

    timeLabel.setText(currentTime + " / " + totalTime, juce::dontSendNotification);


    //------------------------ Bonus(Dynamic Mood Theme)-------------------------------------

    double speed = playerAudio.getspeed();
    juce::Colour target;
    if (speed < 0.75)
        target = juce::Colour::fromRGB(255, 150, 50);  
    else if (speed < 1.25)
        target = juce::Colour::fromRGB(100, 180, 255);  
    else
        target = juce::Colour::fromRGB(140, 80, 220);   

 
    const float interp = 0.08f;
    currentBackground = currentBackground.interpolatedWith(target, interp);

    
    repaint();

    progressBar.repaint();
}



void PlayerGUI::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &volumeSlider)
        playerAudio.setGain((float)slider->getValue());

    if (slider == &speedSlider)
    {
        double speed = speedSlider.getValue();
        playerAudio.setspeed(speed);
    }

}
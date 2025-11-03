#include "PlayerGUI.h"

PlayerGUI::PlayerGUI()
{
    // Add buttons
    for (auto* btn : { &loadButton, &restartButton , &stopButton, &playButton, &pauseButton, &startButton,
         &endButton, &muteButton, &loopButton, &setA, &setB, &jumpBack, &jumpForward })
    {
        btn->addListener(this);
        addAndMakeVisible(btn);
    }

    // Volume slider
    volumeSlider.setRange(0.0, 1.0, 0.01);
    volumeSlider.setValue(0.5);
    volumeSlider.addListener(this);
    addAndMakeVisible(volumeSlider);

    // Position slider
    positionSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    positionSlider.addListener(this);
    addAndMakeVisible(positionSlider);

    startTimer(100);
    timeLabel.setText("00:00 / 00:00", juce::dontSendNotification);
    timeLabel.setJustificationType(juce::Justification::centred);
    timeLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    timeLabel.setFont(juce::Font(15.0f, juce::Font::bold));
    addAndMakeVisible(timeLabel);

    
    speedSlider.setRange(0.25, 2.0, 0.25);
    speedSlider.setValue(1.0);
    speedSlider.addListener(this);
    addAndMakeVisible(speedSlider);
    speedSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 50, 20);

    addAndMakeVisible(progressBar);
    


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
    playButton.setBounds(340, y, 80, 40);
    pauseButton.setBounds(440, y, 80, 40);
    startButton.setBounds(540, y, 80, 40);
    endButton.setBounds(640, y, 80, 40);
    muteButton.setBounds(740, y, 80, 40);
    loopButton.setBounds(840, y, 80, 40);
    setA.setBounds(940, y, 80, 40);
    setB.setBounds(1040, y, 80, 40);
    jumpBack.setBounds(1140, y, 80, 40);
    jumpForward.setBounds(1240, y, 80, 40);
    /*prevButton.setBounds(340, y, 80, 40);
    nextButton.setBounds(440, y, 80, 40);*/


    volumeSlider.setBounds(20, 100, getWidth() - 40, 30);
    speedSlider.setBounds(20, 140, getWidth() - 40, 30);
   
    positionSlider.setBounds(20, 180, getWidth() - 40, 30);
    progressBar.setBounds(20, 220, getWidth() - 40, 20);

    int labelWidth = 80;
    int labelHeight = 20;
    timeLabel.setBounds(20, positionSlider.getY() + 5, labelWidth, labelHeight);


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
        loopButton.setButtonText("Loop");
        loopButton.removeColour(juce::TextButton::buttonColourId);

        playerAudio.resetMarkers();
        setA.setButtonText("Marker A");
        setA.removeColour(juce::TextButton::buttonColourId);
        setB.setButtonText("Marker B");
        setB.removeColour(juce::TextButton::buttonColourId);
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

    if (button == &pauseButton)
    {
        playerAudio.stop();
    }

    if (button == &startButton)
    {
        playerAudio.setPosition(0.0);
    }

    if (button == &endButton)
    {
        playerAudio.goToEnd();
    }

    if (button == &muteButton)
    {
        bool state = !playerAudio.ismuted();
        playerAudio.setmute(state);
        muteButton.setButtonText(state ? "unMute" : "Mute");
    }

    if (button == &setA)
    {
        playerAudio.setmarkerA(playerAudio.getPosition());
        setA.setButtonText("Marker A is Set");
        setA.setColour(juce::TextButton::buttonColourId, juce::Colours::green);
    }

    if (button == &setB)
    {
        playerAudio.setmarkerB(playerAudio.getPosition());
        setB.setButtonText("Marker B is Set");
        setB.setColour(juce::TextButton::buttonColourId, juce::Colours::green);
    }

    if (button == &loopButton)
    {
        isLooping = !isLooping;
        playerAudio.setLooping(isLooping);
        if (isLooping)
        {
            loopButton.setButtonText("UnLoop");
            loopButton.setColour(juce::TextButton::buttonColourId, juce::Colours::red);
        }
        else
        {
            loopButton.setButtonText("Loop");
            loopButton.removeColour(juce::TextButton::buttonColourId);

            playerAudio.resetMarkers();
            setA.setButtonText("Marker A");
            setA.removeColour(juce::TextButton::buttonColourId);
            setB.setButtonText("Marker B");
            setB.removeColour(juce::TextButton::buttonColourId);
        }
    }

    if (button == &jumpForward)
    {
        playerAudio.jumpForward(jump);
    }

    if (button == &jumpBack)
    {
        playerAudio.jumpBackward(jump);
    }

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

void PlayerGUI::updateProgressBar()
{
    double pos = playerAudio.getPosition();
    double len = playerAudio.getLength();

    if (len > 0)
        progressValue = pos / len;
    else
        progressValue = 0.0;

    progressBar.repaint();
}

void PlayerGUI::updatePositionSlider()
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
                currentMinutes, currentSeconds,
                totalMinutes, totalSeconds);

            timeLabel.setText(time, juce::dontSendNotification);
        }
}

void PlayerGUI::timerCallback()
{
    updatePositionSlider();  
    updateProgressBar();   

    double speed = playerAudio.getspeed();
    double mix = juce::jlimit(0.0, 1.0, (speed - 0.25) / (2.0 - 0.25));
    juce::Colour target = juce::Colours::blue.interpolatedWith(juce::Colours::red, mix);

    const float interp = 0.08f;
    currentBackground = currentBackground.interpolatedWith(target, interp);


    repaint();

}
void PlayerGUI::sliderDragStarted(juce::Slider* slider)
{
        if (slider == &positionSlider)
        {
            isDragging = true;
        }
}

void PlayerGUI::sliderDragEnded(juce::Slider* slider)
{
        if (slider == &positionSlider)
        {
            isDragging = false;
            double newPosition = positionSlider.getValue();
            playerAudio.setPosition(newPosition);
        }
}


void PlayerGUI::loadSession()
{
    playerAudio.loadSession();
}

void PlayerGUI::saveSession()
{
    playerAudio.saveSession();
}


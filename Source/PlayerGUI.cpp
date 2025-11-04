#include "PlayerGUI.h"
#include<vector>

PlayerGUI::PlayerGUI()
{
    // Add buttons
    for (auto* btn : { &loadButton, &restartButton , &stopButton, &playButton, &pauseButton, &startButton,
                       &endButton, &nextButton, &prevButton, &muteButton, &loopButton, &setA, &setB, &removeButton, &clearButton,
                       &jumpBack, &jumpForward,

                       & loadButton2,& restartButton2 ,& stopButton2,& playButton2,& pauseButton2,& startButton2,
                       & endButton2, &nextButton2, &prevButton2, &muteButton2,&loopButton2,&setA2,&setB2, &removeButton2, 
                       &clearButton2, &jumpBack2,&jumpForward2 })
    {
        btn->addListener(this);
        addAndMakeVisible(btn);
    }

    // Volume slider
    volumeSlider.setRange(0.0, 1.0, 0.01);
    volumeSlider.setValue(0.5);
    volumeSlider.addListener(this);
    addAndMakeVisible(volumeSlider);

    volumeSlider2.setRange(0.0, 1.0, 0.01);
    volumeSlider2.setValue(0.5);
    volumeSlider2.addListener(this);
    addAndMakeVisible(volumeSlider2);

    // Position slider
    positionSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    positionSlider.addListener(this);
    addAndMakeVisible(positionSlider);

    positionSlider2.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    positionSlider2.addListener(this);
    addAndMakeVisible(positionSlider2);

    // Meta data label
    metadataLabel1.setText("Track 1: -", juce::dontSendNotification);
    addAndMakeVisible(metadataLabel1);
    metadataLabel2.setText("Track 2: -", juce::dontSendNotification);
    addAndMakeVisible(metadataLabel2);
    
    // Playlist box
    playlistBox1.setModel(this);
    addAndMakeVisible(playlistBox1);
    playlistBox2.setModel(this);
    addAndMakeVisible(playlistBox2);

    // Time label
    timeLabel.setText("00:00 / 00:00", juce::dontSendNotification);
    timeLabel.setJustificationType(juce::Justification::centred);
    timeLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    timeLabel.setFont(juce::Font(15.0f, juce::Font::bold));
    addAndMakeVisible(timeLabel);

    timeLabel2.setText("00:00 / 00:00", juce::dontSendNotification);
    timeLabel2.setJustificationType(juce::Justification::centred);
    timeLabel2.setColour(juce::Label::textColourId, juce::Colours::white);
    timeLabel2.setFont(juce::Font(15.0f, juce::Font::bold));
    addAndMakeVisible(timeLabel2);
    
    // Speed slider
    speedSlider.setRange(0.25, 2.0, 0.25);
    speedSlider.setValue(1.0);
    speedSlider.addListener(this);
    addAndMakeVisible(speedSlider);
    //speedSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 50, 20);

    speedSlider2.setRange(0.25, 2.0, 0.25);
    speedSlider2.setValue(1.0);
    speedSlider2.addListener(this);
    addAndMakeVisible(speedSlider2);
    //speedSlider2.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 50, 20);

    // Progress bar
    addAndMakeVisible(progressBar);
    addAndMakeVisible(progressBar2);

    startTimer(100);

}

PlayerGUI::~PlayerGUI() {}


void PlayerGUI::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    playerAudio.prepareToPlay(samplesPerBlockExpected, sampleRate);
    playerAudio2.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void PlayerGUI::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    playerAudio.getNextAudioBlock(bufferToFill);
    playerAudio2.getNextAudioBlock(bufferToFill);
}

void PlayerGUI::releaseResources()
{
    playerAudio.releaseResources();
    playerAudio2.releaseResources();
}


void PlayerGUI::paint(juce::Graphics& g)
{
    g.fillAll(currentBackground);
}

void PlayerGUI::resized()
{
    int width = getWidth();
    int height = getHeight();
    int halfHeight = height / 2;   // divide window in half
    int labelWidth = 80;
    int labelHeight = 20;

    {
        int y = 20;
        //int spacing = 30;

        loadButton.setBounds(20, y, 100, 40);
        restartButton.setBounds(140, y, 80, 40);
        stopButton.setBounds(240, y, 80, 40);
        playButton.setBounds(340, y, 80, 40);
        pauseButton.setBounds(440, y, 80, 40);
        startButton.setBounds(540, y, 80, 40);
        endButton.setBounds(640, y, 80, 40);
        muteButton.setBounds(740, y, 80, 40);
        prevButton.setBounds(840, y, 80, 40);
        nextButton.setBounds(940, y, 80, 40);
        loopButton.setBounds(1040, y, 80, 40);
        setA.setBounds(1140, y, 80, 40);
        setB.setBounds(1240, y, 80, 40);
        y += 50;
        removeButton.setBounds(20, y, 80, 40);
        clearButton.setBounds(140, y, 80, 40);
        jumpBack.setBounds(240, y, 80, 40);
        jumpForward.setBounds(340, y, 80, 40);

        y += 70;
        volumeSlider.setBounds(20, y, width - 40, 30);
        y += 40;
        speedSlider.setBounds(20, y, width - 40, 30);
        y += 40;
        positionSlider.setBounds(120, y, width - 140, 30);
        y += 40;
        progressBar.setBounds(20, y, width - 40, 20);

        /*  int labelWidth = 80;
          int labelHeight = 20;*/
        timeLabel.setBounds(20, positionSlider.getY() + 5, labelWidth, labelHeight);

        metadataLabel1.setBounds(170, y + 30, width - 180, 20);
        playlistBox1.setBounds(20, y + 60, width - 40, 30);
    }
    
    {
        int y = halfHeight + 20;

        loadButton2.setBounds(20, y, 100, 40);
        restartButton2.setBounds(140, y, 80, 40);
        stopButton2.setBounds(240, y, 80, 40);
        playButton2.setBounds(340, y, 80, 40);
        pauseButton2.setBounds(440, y, 80, 40);
        startButton2.setBounds(540, y, 80, 40);
        endButton2.setBounds(640, y, 80, 40);
        muteButton2.setBounds(740, y, 80, 40);
        prevButton2.setBounds(840, y, 80, 40);
        nextButton2.setBounds(940, y, 80, 40);
        loopButton2.setBounds(1040, y, 80, 40);
        setA2.setBounds(1140, y, 80, 40);
        setB2.setBounds(1240, y, 80, 40);
        y += 50;
        removeButton2.setBounds(20, y, 80, 40);
        clearButton2.setBounds(140, y, 80, 40);
        jumpBack2.setBounds(240, y, 80, 40);
        jumpForward2.setBounds(340, y, 80, 40);

        y += 70;
        volumeSlider2.setBounds(20, y, width - 40, 30);
        y += 40;
        speedSlider2.setBounds(20, y, width - 40, 30);
        y += 40;
        positionSlider2.setBounds(120, y, width - 140, 30);
        y += 40;
        progressBar2.setBounds(20, y, width - 40, 20);

        timeLabel2.setBounds(20, positionSlider2.getY() + 5, labelWidth, labelHeight);

        metadataLabel2.setBounds(170, y + 30, width - 180, 20);
        playlistBox2.setBounds(20, y + 60, width - 40, 30);
    }
}

void PlayerGUI::addFilesToPlaylist(int trackNumber)
{
    fileChooser = std::make_unique<juce::FileChooser>("Select audio files...", juce::File{}, "*.wav;*.mp3");
    fileChooser->launchAsync(juce::FileBrowserComponent::openMode,
        [this, trackNumber](const juce::FileChooser& chooser)
        {
            auto files = chooser.getResults();
            if (trackNumber == 1)
            {
                for (auto& file : files) 
                { 
                    playlist1.add(file);
                    playlistFiles1.add(file.getFileName()); 
                }

                if (currentIndex1 == -1 && playlist1.size() > 0) 
                { 
                    currentIndex1 = 0; loadAndPlayFile(playlist1[0], 1); 
                }
                playlistBox1.updateContent();

                loopButton.setButtonText("Loop");
                loopButton.removeColour(juce::TextButton::buttonColourId);

                playerAudio.resetMarkers();
                setA.setButtonText("Marker A");
                setA.removeColour(juce::TextButton::buttonColourId);
                setB.setButtonText("Marker B");
                setB.removeColour(juce::TextButton::buttonColourId);
            }
            else
            {
                for (auto& file : files) 
                { 
                    playlist2.add(file); 
                    playlistFiles2.add(file.getFileName()); 
                }

                if (currentIndex2 == -1 && playlist2.size() > 0)
                { 
                    currentIndex2 = 0; 
                    loadAndPlayFile(playlist2[0], 2); 
                }
                playlistBox2.updateContent();


                loopButton2.setButtonText("Loop");
                loopButton2.removeColour(juce::TextButton::buttonColourId);

                playerAudio2.resetMarkers();
                setA2.setButtonText("Marker A");
                setA2.removeColour(juce::TextButton::buttonColourId);
                setB2.setButtonText("Marker B");
                setB2.removeColour(juce::TextButton::buttonColourId);
            }
        });
}

void PlayerGUI::loadAndPlayFile(const juce::File& file, int trackNumber)
{
    if (trackNumber == 1)
    {
        if (playerAudio.LoadFile(file)) 
        { 
            playerAudio.setGain((float)volumeSlider.getValue()); 
            playerAudio.start(); 
        }
    }
    else
    {
        if (playerAudio2.LoadFile(file))
        { 
            playerAudio2.setGain((float)volumeSlider2.getValue()); 
            playerAudio2.start(); 
        }
    }
    updateMetadataDisplay(file, trackNumber);
}

void PlayerGUI::updateMetadataDisplay(const juce::File& file, int trackNumber)
{
    if (!file.existsAsFile()) return;

    juce::AudioFormatManager fm;
    fm.registerBasicFormats();
    std::unique_ptr<juce::AudioFormatReader> reader(fm.createReaderFor(file));

    double duration = 0.0;
    if (reader) duration = reader->lengthInSamples / reader->sampleRate;

    juce::String title, artist, album;
    if (reader)
    {
        auto metadata = reader->metadataValues;
        if (metadata.containsKey("title")) title = metadata["title"];
        if (metadata.containsKey("artist")) artist = metadata["artist"];
        if (metadata.containsKey("album")) album = metadata["album"];
    }

    juce::String text;
    if (title.isNotEmpty() || artist.isNotEmpty() || album.isNotEmpty())
        text = "Title: " + title + ", Artist: " + artist + ", Album: " + album +
        ", Duration: " + juce::String(duration, 2) + " s";
    else
        text = "Filename: " + file.getFileName() + ", Duration: " + juce::String(duration, 2) + " s";

    if (trackNumber == 1) metadataLabel1.setText(text, juce::dontSendNotification);
    else metadataLabel2.setText(text, juce::dontSendNotification);
}

void PlayerGUI::removeSelected(int trackNumber)
{
    if (trackNumber == 1 && currentIndex1 >= 0)
    {
        playlist1.remove(currentIndex1);
        playlistFiles1.remove(currentIndex1);
        if (playlist1.size() > 0)
        {
            currentIndex1 = juce::jlimit(0, playlist1.size() - 1, currentIndex1);
            loadAndPlayFile(playlist1[currentIndex1], 1);
        }
        else currentIndex1 = -1;
        playlistBox1.updateContent();
    }
    else if (trackNumber == 2 && currentIndex2 >= 0)
    {
        playlist2.remove(currentIndex2);
        playlistFiles2.remove(currentIndex2);
        if (playlist2.size() > 0)
        {
            currentIndex2 = juce::jlimit(0, playlist2.size() - 1, currentIndex2);
            loadAndPlayFile(playlist2[currentIndex2], 2);
        }
        else currentIndex2 = -1;
        playlistBox2.updateContent();
    }
}

void PlayerGUI::clearPlaylist(int trackNumber)
{
    if (trackNumber == 1)
    {
        playlist1.clear(); 
        playlistFiles1.clear(); 
        currentIndex1 = -1; 
        playlistBox1.updateContent();
    }
    else
    {
        playlist2.clear(); 
        playlistFiles2.clear(); 
        currentIndex2 = -1; 
        playlistBox2.updateContent();
    }
}

int PlayerGUI::getNumRows()
{
    return playlist1.size();
}

int PlayerGUI::getNumRows2()
{
    return playlist2.size();
}

void PlayerGUI::paintListBoxItem(int row, juce::Graphics& g, int width, int height, bool selected)
{
    if (selected) g.fillAll(juce::Colours::lightblue);
    if (row >= 0 && row < playlistFiles1.size())
    {
        g.drawText(playlistFiles1[row], 5, 0, width - 10, height, juce::Justification::centredLeft);
    }
}

void PlayerGUI::paintListBoxItem2(int row, juce::Graphics& g, int width, int height, bool selected)
{
    if (selected) g.fillAll(juce::Colours::lightblue);
    if (row >= 0 && row < playlistFiles2.size())
    {
        g.drawText(playlistFiles2[row], 5, 0, width - 10, height, juce::Justification::centredLeft);
    }
}

void PlayerGUI::selectedRowsChanged(int lastRow)
{
    if (lastRow >= 0 && lastRow < playlist1.size())
    {
        currentIndex1 = lastRow;
        loadAndPlayFile(playlist1[currentIndex1], 1);
    }
}

void PlayerGUI::selectedRowsChanged2(int lastRow)
{
    if (lastRow >= 0 && lastRow < playlist2.size())
    {
        currentIndex2 = lastRow;
        loadAndPlayFile(playlist2[currentIndex2], 2);
    }
}

void PlayerGUI::buttonClicked(juce::Button* button)
{
    // Buttons for Track 1
    if (button == &loadButton)
    {
        addFilesToPlaylist(1);
    }

    else if (button == &restartButton)
    {
        playerAudio.start();
    }

    else if (button == &stopButton)
    {
        playerAudio.stop();
        playerAudio.setPosition(0.0);
    }

    else if (button == &playButton)
    {
        playerAudio.start();
    }

    else if (button == &pauseButton)
    {
        playerAudio.stop();
    }

    else if (button == &startButton)
    {
        playerAudio.setPosition(0.0);
    }

    else if (button == &endButton)
    {
        playerAudio.goToEnd();
    }

    else if (button == &muteButton)
    {
        bool state = !playerAudio.ismuted();
        playerAudio.setmute(state);
        muteButton.setButtonText(state ? "unMute" : "Mute");
    }

    else if (button == &prevButton && currentIndex1 >= 0 && playlist1.size() > 0)
    { 
        currentIndex1 = (currentIndex1 - 1 + playlist1.size()) % playlist1.size();
        loadAndPlayFile(playlist1[currentIndex1], 1); 
    }

    else if (button == &nextButton && currentIndex1 >= 0 && playlist1.size() > 0)
    { 
        currentIndex1 = (currentIndex1 + 1) % playlist1.size(); 
        loadAndPlayFile(playlist1[currentIndex1], 1); 
    }

    else if (button == &setA)
    {
        playerAudio.setmarkerA(playerAudio.getPosition());
        setA.setButtonText("Marker A is Set");
        setA.setColour(juce::TextButton::buttonColourId, juce::Colours::green);
    }

    else if (button == &setB)
    {
        playerAudio.setmarkerB(playerAudio.getPosition());
        setB.setButtonText("Marker B is Set");
        setB.setColour(juce::TextButton::buttonColourId, juce::Colours::green);
    }

    else if (button == &loopButton)
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

    else if (button == &removeButton)
    {
        removeSelected(1);
    }

    else if (button == &clearButton)
    {
        clearPlaylist(1);
    }

    else if (button == &jumpForward)
    {
        playerAudio.jumpForward(jump);
    }

    else if (button == &jumpBack)
    {
        playerAudio.jumpBackward(jump);
    }

    // Buttons for Track 2
    else if (button == &loadButton2)
    {
        addFilesToPlaylist(2);
    }

    else if (button == &restartButton2)
    {
        playerAudio2.start();
    }

    else if (button == &stopButton2)
    {
        playerAudio2.stop();
        playerAudio2.setPosition(0.0);
    }

    else if (button == &playButton2)
    {
        playerAudio2.start();
    }

    else if (button == &pauseButton2)
    {
        playerAudio2.stop();
    }

    else if (button == &startButton2)
    {
        playerAudio2.setPosition(0.0);
    }

    else if (button == &endButton2)
    {
        playerAudio2.goToEnd();
    }

    else if (button == &muteButton2)
    {
        bool state2 = !playerAudio2.ismuted();
        playerAudio2.setmute(state2);
        muteButton2.setButtonText(state2 ? "unMute" : "Mute");
    }

    else if(button == &prevButton2 && currentIndex2 >= 0 && playlist2.size() > 0)
    { 
        currentIndex2 = (currentIndex2 - 1 + playlist2.size()) % playlist2.size();
        loadAndPlayFile(playlist2[currentIndex2], 2); 
    }

    else if (button == &nextButton2 && currentIndex2 >= 0 && playlist2.size() > 0) 
    { 
        currentIndex2 = (currentIndex2 + 1) % playlist2.size(); 
        loadAndPlayFile(playlist2[currentIndex2], 2); 
    }

    else if (button == &setA2)
    {
        playerAudio2.setmarkerA(playerAudio2.getPosition());
        setA2.setButtonText("Marker A is Set");
        setA2.setColour(juce::TextButton::buttonColourId, juce::Colours::green);
    }

    else if (button == &setB2)
    {
        playerAudio2.setmarkerB(playerAudio2.getPosition());
        setB2.setButtonText("Marker B is Set");
        setB2.setColour(juce::TextButton::buttonColourId, juce::Colours::green);
    }

    else if (button == &loopButton2)
    {
        isLooping2 = !isLooping2;
        playerAudio2.setLooping(isLooping2);
        if (isLooping2)
        {
            loopButton2.setButtonText("UnLoop");
            loopButton2.setColour(juce::TextButton::buttonColourId, juce::Colours::red);
        }
        else
        {
            loopButton2.setButtonText("Loop");
            loopButton2.removeColour(juce::TextButton::buttonColourId);

            playerAudio2.resetMarkers();
            setA2.setButtonText("Marker A");
            setA2.removeColour(juce::TextButton::buttonColourId);
            setB2.setButtonText("Marker B");
            setB2.removeColour(juce::TextButton::buttonColourId);
        }
    }

    else if (button == &removeButton2)
    {
        removeSelected(2);
    }

    else if (button == &clearButton2)
    {
        clearPlaylist(2);
    }

    else if (button == &jumpForward2)
    {
        playerAudio2.jumpForward(jump);
    }

    else if (button == &jumpBack2)
    {
        playerAudio2.jumpBackward(jump);
    }
}

//void PlayerGUI::buttonClicked(juce::Button* button)             
//{
//    if (button == &loadButton)
//    {
//        juce::FileChooser chooser("Select audio files...",
//            juce::File{},
//            "*.wav;*.mp3");
//
//        fileChooser = std::make_unique<juce::FileChooser>(
//            "Select an audio file...",
//            juce::File{},
//            "*.wav;*.mp3");
//
//        fileChooser->launchAsync(
//            juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles,
//            [this](const juce::FileChooser& fc)
//            {
//                auto file = fc.getResult();
//                if (file.existsAsFile())
//                {
//                    playerAudio.LoadFile(file);
//                }
//            });
//        loopButton.setButtonText("Loop");
//        loopButton.removeColour(juce::TextButton::buttonColourId);
//
//        playerAudio.resetMarkers();
//        setA.setButtonText("Marker A");
//        setA.removeColour(juce::TextButton::buttonColourId);
//        setB.setButtonText("Marker B");
//        setB.removeColour(juce::TextButton::buttonColourId);
//    }
//
//    if (button == &restartButton)
//    {
//        playerAudio.start();
//    }
//
//    if (button == &stopButton)
//    {
//        playerAudio.stop();
//        playerAudio.setPosition(0.0);
//    }
//
//    if (button == &pauseButton)
//    {
//        playerAudio.stop();
//    }
//
//    if (button == &startButton)
//    {
//        playerAudio.setPosition(0.0);
//    }
//
//    if (button == &endButton)
//    {
//        playerAudio.goToEnd();
//    }
//
//    if (button == &muteButton)
//    {
//        bool state = !playerAudio.ismuted();
//        playerAudio.setmute(state);
//        muteButton.setButtonText(state ? "unMute" : "Mute");
//    }
//
//    if (button == &setA)
//    {
//        playerAudio.setmarkerA(playerAudio.getPosition());
//        setA.setButtonText("Marker A is Set");
//        setA.setColour(juce::TextButton::buttonColourId, juce::Colours::green);
//    }
//
//    if (button == &setB) 
//    {
//        playerAudio.setmarkerB(playerAudio.getPosition());
//        setB.setButtonText("Marker B is Set");
//        setB.setColour(juce::TextButton::buttonColourId, juce::Colours::green);
//    }
//
//    if (button == &loopButton)
//    {
//        isLooping = !isLooping;
//        playerAudio.setLooping(isLooping);
//        if (isLooping)
//        {
//            loopButton.setButtonText("UnLoop");
//            loopButton.setColour(juce::TextButton::buttonColourId, juce::Colours::red);
//        }
//        else
//        {
//            loopButton.setButtonText("Loop");
//            loopButton.removeColour(juce::TextButton::buttonColourId);
//
//            playerAudio.resetMarkers();
//            setA.setButtonText("Marker A");
//            setA.removeColour(juce::TextButton::buttonColourId);
//            setB.setButtonText("Marker B");
//            setB.removeColour(juce::TextButton::buttonColourId);
//        }
//    }
//
//    if (button == &jumpForward)
//    {
//        playerAudio.jumpForward(jump);
//    }
//
//    if (button == &jumpBack)
//    {
//        playerAudio.jumpBackward(jump);
//    }
//
//}


void PlayerGUI::sliderValueChanged(juce::Slider* slider)
{
    // Sliders for Track 1
    if (slider == &volumeSlider)
    {
        playerAudio.setGain((float)slider->getValue());
    }

    else if (slider == &speedSlider)
    {
        double speed = speedSlider.getValue();
        playerAudio.setspeed(speed);
    }

    // Sliders for Track 2
    else if (slider == &volumeSlider2)
        playerAudio2.setGain((float)slider->getValue());

    else if (slider == &speedSlider2)
    {
        double speed2 = speedSlider2.getValue();
        playerAudio2.setspeed(speed2);
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

    double pos2 = playerAudio2.getPosition();
    double len2 = playerAudio2.getLength();

    if (len2 > 0)
        progressValue2 = pos2 / len2;
    else
        progressValue2 = 0.0;

    progressBar2.repaint();
}

void PlayerGUI::updatePositionSlider()
{
        if (!isDragging && currentIndex1 >= 0)
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

        if (!isDragging2 && currentIndex2 >= 0)
        {
            double currentPosition = playerAudio2.getPosition();
            double totalLength = playerAudio2.getLength();

            positionSlider2.setRange(0.0, totalLength, 0.01);
            positionSlider2.setValue(currentPosition, juce::dontSendNotification);

            int currentInt = static_cast<int>(currentPosition);
            int totalInt = static_cast<int>(totalLength);

            int currentMinutes = currentInt / 60;
            int currentSeconds = currentInt % 60;
            int totalMinutes = totalInt / 60;
            int totalSeconds = totalInt % 60;

            juce::String time = juce::String::formatted("%02d:%02d / %02d:%02d",
                currentMinutes, currentSeconds,
                totalMinutes, totalSeconds);

            timeLabel2.setText(time, juce::dontSendNotification);
        }

}

void PlayerGUI::timerCallback()
{
    updatePositionSlider();  
    updateProgressBar();   

    // Speed for Track 1
    double speed = playerAudio.getspeed();
    double mix = juce::jlimit(0.0, 1.0, (speed - 0.25) / (2.0 - 0.25));
    juce::Colour target = juce::Colours::blue.interpolatedWith(juce::Colours::red, mix);

    const float interp = 0.08f;
    currentBackground = currentBackground.interpolatedWith(target, interp);

    // Speed for Track 2
    double speed2 = playerAudio2.getspeed();
    double mix2 = juce::jlimit(0.0, 1.0, (speed2 - 0.25) / (2.0 - 0.25));
    juce::Colour target2 = juce::Colours::blue.interpolatedWith(juce::Colours::red, mix2);

    currentBackground2 = currentBackground2.interpolatedWith(target2, interp);

    repaint();

}

void PlayerGUI::sliderDragStarted(juce::Slider* slider)
{
        if (slider == &positionSlider)
        {
            isDragging = true;
        }
        else if(slider == &positionSlider2)
        {
            isDragging2 = true;
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
        else if (slider == &positionSlider2)
        {
            isDragging2 = false;
            double newPosition2 = positionSlider2.getValue();
            playerAudio2.setPosition(newPosition2);
        }
}


void PlayerGUI::loadSession()
{
    playerAudio.loadSession();
    playerAudio2.loadSession();
}

void PlayerGUI::saveSession()
{ 
    playerAudio.saveSession();
    playerAudio2.saveSession();
}


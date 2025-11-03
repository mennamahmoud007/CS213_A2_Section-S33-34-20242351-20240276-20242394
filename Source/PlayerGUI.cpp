#include "PlayerGUI.h"
#include<vector>
PlayerGUI::PlayerGUI()
{
    for (auto* btn : { &loadButton1, &playButton1, &pauseButton1, &stopButton1,
                       &nextButton1, &prevButton1, &loopButton1, &removeButton1, &clearButton1,
                       &loadButton2, &playButton2, &pauseButton2, &stopButton2,
                       &nextButton2, &prevButton2, &loopButton2, &removeButton2, &clearButton2 })
    {
        btn->addListener(this);
        addAndMakeVisible(btn);
    }

    volumeSlider1.setRange(0.0, 1.0, 0.01);
    volumeSlider1.setValue(0.5);
    volumeSlider1.addListener(this);
    addAndMakeVisible(volumeSlider1);

    volumeSlider2.setRange(0.0, 1.0, 0.01);
    volumeSlider2.setValue(0.5);
    volumeSlider2.addListener(this);
    addAndMakeVisible(volumeSlider2);

    metadataLabel1.setText("Track 1: -", juce::dontSendNotification);
    addAndMakeVisible(metadataLabel1);
    metadataLabel2.setText("Track 2: -", juce::dontSendNotification);
    addAndMakeVisible(metadataLabel2);

    playlistBox1.setModel(this);
    addAndMakeVisible(playlistBox1);
    playlistBox2.setModel(this);
    addAndMakeVisible(playlistBox2);

    startTimer(100);
}

PlayerGUI::~PlayerGUI() {}

void PlayerGUI::paint(juce::Graphics&) {}

void PlayerGUI::resized()
{
    int y = 10;
    int spacing = 30;

    loadButton1.setBounds(10, y, 80, 25);
    playButton1.setBounds(100, y, 60, 25);
    pauseButton1.setBounds(170, y, 60, 25);
    stopButton1.setBounds(240, y, 60, 25);
    prevButton1.setBounds(310, y, 60, 25);
    nextButton1.setBounds(380, y, 60, 25);
    loopButton1.setBounds(450, y, 60, 25);
    removeButton1.setBounds(520, y, 80, 25);
    clearButton1.setBounds(610, y, 80, 25);
    volumeSlider1.setBounds(10, y + spacing, getWidth() - 20, 20);
    positionSlider1.setBounds(10, y + spacing + 30, getWidth() - 20, 20);
    timeLabel1.setBounds(10, y + spacing + 60, 150, 20);
    metadataLabel1.setBounds(170, y + spacing + 60, getWidth() - 180, 20);
    playlistBox1.setBounds(10, y + spacing + 90, getWidth() - 20, getHeight() - (y + spacing + 100));

    y += 200;
    loadButton2.setBounds(10, y, 80, 25);
    playButton2.setBounds(100, y, 60, 25);
    pauseButton2.setBounds(170, y, 60, 25);
    stopButton2.setBounds(240, y, 60, 25);
    prevButton2.setBounds(310, y, 60, 25);
    nextButton2.setBounds(380, y, 60, 25);
    loopButton2.setBounds(450, y, 60, 25);
    removeButton2.setBounds(520, y, 80, 25);
    clearButton2.setBounds(610, y, 80, 25);
    volumeSlider2.setBounds(10, y + spacing, getWidth() - 20, 20);
    positionSlider2.setBounds(10, y + spacing + 30, getWidth() - 20, 20);
    timeLabel2.setBounds(10, y + spacing + 60, 150, 20);
    metadataLabel2.setBounds(170, y + spacing + 60, getWidth() - 180, 20);
    playlistBox2.setBounds(10, y + spacing + 90, getWidth() - 20, getHeight() - (y + spacing + 100));
}

void PlayerGUI::buttonClicked(juce::Button* button)
{
    if (button == &loadButton1) addFilesToPlaylist(1);
    if (button == &playButton1 && currentIndex1 >= 0) playerAudio1.start();
    if (button == &pauseButton1 && currentIndex1 >= 0) playerAudio1.stop();
    if (button == &stopButton1 && currentIndex1 >= 0) { playerAudio1.stop(); playerAudio1.setPosition(0.0); }
    if (button == &nextButton1 && currentIndex1 >= 0 && playlist1.size() > 0) { currentIndex1 = (currentIndex1 + 1) % playlist1.size(); loadAndPlayFile(playlist1[currentIndex1], 1); }
    if (button == &prevButton1 && currentIndex1 >= 0 && playlist1.size() > 0) { currentIndex1 = (currentIndex1 - 1 + playlist1.size()) % playlist1.size(); loadAndPlayFile(playlist1[currentIndex1], 1); }
    if (button == &loopButton1) { isLooping1 = !isLooping1; playerAudio1.setLooping(isLooping1); loopButton1.setButtonText(isLooping1 ? "UnLoop" : "Loop"); }
    if (button == &removeButton1) removeSelected(1);
    if (button == &clearButton1) clearPlaylist(1);

    if (button == &loadButton2) addFilesToPlaylist(2);
    if (button == &playButton2 && currentIndex2 >= 0) playerAudio2.start();
    if (button == &pauseButton2 && currentIndex2 >= 0) playerAudio2.stop();
    if (button == &stopButton2 && currentIndex2 >= 0) { playerAudio2.stop(); playerAudio2.setPosition(0.0); }
    if (button == &nextButton2 && currentIndex2 >= 0 && playlist2.size() > 0) { currentIndex2 = (currentIndex2 + 1) % playlist2.size(); loadAndPlayFile(playlist2[currentIndex2], 2); }
    if (button == &prevButton2 && currentIndex2 >= 0 && playlist2.size() > 0) { currentIndex2 = (currentIndex2 - 1 + playlist2.size()) % playlist2.size(); loadAndPlayFile(playlist2[currentIndex2], 2); }
    if (button == &loopButton2) { isLooping2 = !isLooping2; playerAudio2.setLooping(isLooping2); loopButton2.setButtonText(isLooping2 ? "UnLoop" : "Loop"); }
    if (button == &removeButton2) removeSelected(2);
    if (button == &clearButton2) clearPlaylist(2);
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
                for (auto& file : files) { playlist1.add(file); playlistFiles1.add(file.getFileName()); }
                if (currentIndex1 == -1 && playlist1.size() > 0) { currentIndex1 = 0; loadAndPlayFile(playlist1[0], 1); }
                playlistBox1.updateContent();
            }
            else
            {
                for (auto& file : files) { playlist2.add(file); playlistFiles2.add(file.getFileName()); }
                if (currentIndex2 == -1 && playlist2.size() > 0) { currentIndex2 = 0; loadAndPlayFile(playlist2[0], 2); }
                playlistBox2.updateContent();
            }
        });
}

void PlayerGUI::loadAndPlayFile(const juce::File& file, int trackNumber)
{
    if (trackNumber == 1)
    {
        if (playerAudio1.loadFile(file)) { playerAudio1.setGain((float)volumeSlider1.getValue()); playerAudio1.start(); }
    }
    else
    {
        if (playerAudio2.loadFile(file)) { playerAudio2.setGain((float)volumeSlider2.getValue()); playerAudio2.start(); }
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
        playlist1.clear(); playlistFiles1.clear(); currentIndex1 = -1; playlistBox1.updateContent();
    }
    else
    {
        playlist2.clear(); playlistFiles2.clear(); currentIndex2 = -1; playlistBox2.updateContent();
    }
}

void PlayerGUI::timerCallback()
{
    if (!isDragging1 && currentIndex1 >= 0)
    {
        double pos = playerAudio1.getPosition();
        double len = playerAudio1.getLength();
        positionSlider1.setRange(0.0, len, 0.01);
        positionSlider1.setValue(pos, juce::dontSendNotification);
        int curMin = (int)(pos / 60), curSec = (int)pos % 60;
        int totMin = (int)(len / 60), totSec = (int)len % 60;
        timeLabel1.setText(juce::String::formatted("%02d:%02d / %02d:%02d", curMin, curSec, totMin, totSec), juce::dontSendNotification);
    }

    if (!isDragging2 && currentIndex2 >= 0)
    {
        double pos = playerAudio2.getPosition();
        double len = playerAudio2.getLength();
        positionSlider2.setRange(0.0, len, 0.01);
        positionSlider2.setValue(pos, juce::dontSendNotification);
        int curMin = (int)(pos / 60), curSec = (int)pos % 60;
        int totMin = (int)(len / 60), totSec = (int)len % 60;
        timeLabel2.setText(juce::String::formatted("%02d:%02d / %02d:%02d", curMin, curSec, totMin, totSec), juce::dontSendNotification);
    }
}

void PlayerGUI::sliderDragStarted(juce::Slider* slider)
{
    if (slider == &volumeSlider1) isDragging1 = true;
    if (slider == &volumeSlider2) isDragging2 = true;
}

void PlayerGUI::sliderDragEnded(juce::Slider* slider)
{
    if (slider == &volumeSlider1) { isDragging1 = false; playerAudio1.setGain((float)volumeSlider1.getValue()); }
    if (slider == &volumeSlider2) { isDragging2 = false; playerAudio2.setGain((float)volumeSlider2.getValue()); }
}

void PlayerGUI::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &volumeSlider1) playerAudio1.setGain((float)volumeSlider1.getValue());
    if (slider == &volumeSlider2) playerAudio2.setGain((float)volumeSlider2.getValue());
}

int PlayerGUI::getNumRows() { return playlist1.size(); }

void PlayerGUI::paintListBoxItem(int row, juce::Graphics& g, int width, int height, bool selected)
{
    if (selected) g.fillAll(juce::Colours::lightblue);
    if (row >= 0 && row < playlistFiles1.size()) g.drawText(playlistFiles1[row], 5, 0, width - 10, height, juce::Justification::centredLeft);
}

void PlayerGUI::selectedRowsChanged(int lastRow)
{
    if (lastRow >= 0 && lastRow < playlist1.size())
    {
        currentIndex1 = lastRow;
        loadAndPlayFile(playlist1[currentIndex1], 1);
    }
}

void PlayerGUI::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    playerAudio1.prepareToPlay(samplesPerBlockExpected, sampleRate);
    playerAudio2.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void PlayerGUI::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    playerAudio1.getNextAudioBlock(bufferToFill);
    playerAudio2.getNextAudioBlock(bufferToFill);
}

void PlayerGUI::releaseResources()
{
    playerAudio1.releaseResources();
    playerAudio2.releaseResources();
}

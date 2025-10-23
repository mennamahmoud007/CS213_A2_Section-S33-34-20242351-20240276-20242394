﻿#pragma warning(disable : 26495)
#include <JuceHeader.h> 
#include "MainComponent.h"

MainComponent::MainComponent()
{
    formatManager.registerBasicFormats();

    // Add buttons
    for (auto* btn : { &loadButton, &restartButton , &stopButton })
    {
        btn->addListener(this);
        addAndMakeVisible(btn);
    }
    for (auto* btn : { &loadButton, &restartButton , &stopButton })
    {
        btn->addListener(this);
        addAndMakeVisible(btn);
    }

    for (auto* btn : { &playButton, &pauseButton, &startButton, &endButton })
    {
        btn->addListener(this);
        addAndMakeVisible(btn);
    }

    // Volume slider
    volumeSlider.setRange(0.0, 1.0, 0.01);
    volumeSlider.setValue(0.5);
    volumeSlider.addListener(this);
    addAndMakeVisible(volumeSlider);

    setSize(500, 250);
    setAudioChannels(0, 2);

}

MainComponent::~MainComponent()
{
    shutdownAudio();
}

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    transportSource.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    transportSource.releaseResources();
}

void MainComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkgrey);
}

void MainComponent::resized()
{
    int y = 20;
    loadButton.setBounds(20, y, 100, 40);
    restartButton.setBounds(130, y, 80, 40);
    stopButton.setBounds(220, y, 80, 40);
    playButton.setBounds(310, y, 80, 40);
    pauseButton.setBounds(400, y, 80, 40);
    startButton.setBounds(490, y, 80, 40);
    endButton.setBounds(580, y, 80, 40);

    volumeSlider.setBounds(20, 100, getWidth() - 40, 30);
}
void MainComponent::buttonClicked(juce::Button* button)
{
    if (button == &loadButton)
    {
        fileChooser = std::make_unique<juce::FileChooser>(
            "Select an audio file...", juce::File{}, "*.wav;*.mp3");

        fileChooser->launchAsync(
            juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles,
            [this](const juce::FileChooser& fc)
            {
                auto file = fc.getResult();
                if (file.existsAsFile())
                {
                    if (auto* reader = formatManager.createReaderFor(file))
                    {
                        transportSource.stop();
                        transportSource.setSource(nullptr);
                        readerSource.reset();

                        readerSource = std::make_unique<juce::AudioFormatReaderSource>(reader, true);
                        transportSource.setSource(readerSource.get(), 0, nullptr, reader->sampleRate);
                        transportSource.start();
                    }
                }
            });
    }

    if (button == &restartButton)
    {
        transportSource.setPosition(0.0);
        transportSource.start();
    }

    if (button == &stopButton)
    {
        transportSource.stop();
        transportSource.setPosition(0.0);
    }

    if (button == &playButton)
    {
        transportSource.start();
    }

    if (button == &pauseButton)
    {
        transportSource.stop(); 
    }

    if (button == &startButton)
    {
        transportSource.setPosition(0.0); 
    }

    if (button == &endButton)
    {
        double length = transportSource.getLengthInSeconds();
        if (length > 0)
            transportSource.setPosition(length - 0.1); 
    }
}

void MainComponent::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &volumeSlider)
        transportSource.setGain((float)slider->getValue());
}
#include "MainComponent.h"

MainComponent::MainComponent()
{
    addAndMakeVisible(player1);
    setSize(500, 250);
    setAudioChannels(0, 2);
   
    player1.prepareToPlay(512, 44100);
    player1.loadSession();
}

MainComponent::~MainComponent()
{
   
    player1.saveSession();
    shutdownAudio();
}

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    player1.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    player1.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    player1.releaseResources();
}

void MainComponent::resized()
{
    player1.setBounds(20, 20, getWidth() - 40, getHeight() - 40);
}
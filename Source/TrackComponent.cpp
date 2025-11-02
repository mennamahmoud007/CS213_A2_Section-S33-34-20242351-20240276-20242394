#include "TrackComponent.h"

TrackComponent::TrackComponent()
{
	formatManager.registerBasicFormats();

    // Add Buttons
    for (auto* btn : { &loadButton, &playButton })
    {
        btn->addListener(this);
        addAndMakeVisible(btn);
    }

    // Volume Slider
    volumeSlider.setRange(0.0, 1.0, 0.01);
    volumeSlider.setValue(0.5);
    volumeSlider.addListener(this);
    addAndMakeVisible(volumeSlider);

}

TrackComponent::~TrackComponent() {}

void TrackComponent::paint(juce::Graphics&)
{
    g.fillAll(juce::Colours::darkgrey);
}

void TrackComponent::resized()
{
    auto area = getLocalBounds().reduced(10);
    loadButton.setBounds(area.removeFromTop(30));
    playButton.setBounds(area.removeFromTop(30));
    volumeSlider.setBounds(area.removeFromTop(40));
}

void TrackComponent::buttonClicked(juce::Button* button)
{

}


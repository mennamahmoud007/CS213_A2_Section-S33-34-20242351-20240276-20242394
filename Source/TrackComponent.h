#pragma once
#include <JuceHeader.h>

class TrackComponent : public juce::Component,
    public juce::Button::Listener,
    public juce::Slider::Listener
{
public:
    TrackComponent();
    ~TrackComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    void buttonClicked(juce::Button* button) override;
    void sliderValueChanged(juce::Slider* slider) override;

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);
    void releaseResources();

private:
    juce::TextButton loadButton{ "Load" };
    juce::TextButton playButton{ "Play" };
    juce::Slider volumeSlider;

    juce::AudioFormatManager formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioTransportSource transportSource;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TrackComponent)
};
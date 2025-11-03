#pragma once							
#include <JuceHeader.h>

class PlayerAudio
{
public:
    PlayerAudio();
    ~PlayerAudio();

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);
    void releaseResources();

    bool LoadFile(const juce::File& file);
    void start();
    void stop();
    void setGain(float gain);
    void setPosition(double pos);
    double getPosition() const;
    double getLength() const;
    void goToEnd();
    void setmute(bool muted);
    bool ismuted()const;
    void setspeed(double speed);
    double getspeed() const;
    void setLooping(bool willLoop);
    void setmarkerA(double position);
    void setmarkerB(double position);
    void resetMarkers();
    void jumpForward(double seconds);
    void jumpBackward(double seconds);
    void saveSession();
    void loadSession();
    bool fadingOut = false;


private:

    juce::AudioFormatManager formatManager;
    juce::AudioTransportSource transportSource;
    juce::File currentFile;

    std::unique_ptr<juce::ResamplingAudioSource> resampleSource;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;

    bool muted = false;
    float lastGain = 1.0f;
    double currentSampleRate = 44100.0;
    double playbackSpeed = 1.0;
    bool isLooping = false;
    bool a_bLooping = false;
    double setA = 0.0, setB = 0.0;
    bool isMarker_A = false, isMarker_B = false;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerAudio)

};
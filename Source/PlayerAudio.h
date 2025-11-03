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

    //task 3
    void setmute(bool muted); 
    bool ismuted()const;
    //task 6
    void setspeed(double speed);
    double getspeed() const;
    //Bonus 2 (task 13)
    void saveSession();
    void loadSession();
    //Bonus 3 (Gentle Stop)
    bool fadingOut = false; 


private:
    
    juce::AudioFormatManager formatManager;
    juce::AudioTransportSource transportSource;
    juce::File currentFile; 


    std::unique_ptr<juce::ResamplingAudioSource> resampleSource;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
   
        //task 3
        bool muted = false; 
        float lastGain = 1.0f;
        //task 6
        double currentSampleRate=44100.0; 
        double playbackSpeed = 1.0;

//JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerAudio)

};

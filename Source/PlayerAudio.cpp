#include "PlayerAudio.h"


PlayerAudio::PlayerAudio()
{
    formatManager.registerBasicFormats();
    resampleSource = std::make_unique<juce::ResamplingAudioSource>(&transportSource, false, 2);
   
}

PlayerAudio::~PlayerAudio()
{
   // transportSource.releaseResources();
}

void PlayerAudio::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    currentSampleRate = sampleRate;
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource->prepareToPlay(samplesPerBlockExpected, sampleRate);

}

void PlayerAudio::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    resampleSource->getNextAudioBlock(bufferToFill);
}

void PlayerAudio::releaseResources()
{
    transportSource.releaseResources();
    resampleSource->releaseResources();
}


bool PlayerAudio::LoadFile(const juce::File& file)
{
    if (file.existsAsFile())
    {
        if (auto* reader = formatManager.createReaderFor(file))
        {
            // ?? Disconnect old source first
            transportSource.stop();
            transportSource.setSource(nullptr);
            readerSource.reset();

            // Create new reader source
            std::unique_ptr<juce::AudioFormatReaderSource> newSource(new juce::AudioFormatReaderSource(reader, true));
            transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
            readerSource.reset(newSource.release());

            transportSource.start();
        }
    }
    return true;
}


void PlayerAudio::start()
{
    transportSource.start();
}

void PlayerAudio::stop()
{
    transportSource.stop();
}

void PlayerAudio::setPosition(double pos)
{
    transportSource.setPosition(pos);
}

double PlayerAudio::getPosition() const
{
    return transportSource.getCurrentPosition();
}

double PlayerAudio::getLength() const
{
    return transportSource.getLengthInSeconds();
}
//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------
void PlayerAudio::setGain(float gain)
{
    lastGain = gain;                 
    if (!muted)
        transportSource.setGain(gain);
}
bool PlayerAudio::ismuted() const
{
    return muted; 
}
void PlayerAudio::setmute(bool newMuted)
{
    if (newMuted)
    {
        lastGain = transportSource.getGain();
        transportSource.setGain(0.0f);
        muted = true;
    }
    else
    {
        transportSource.setGain(lastGain);
        muted = false;
    }
}
//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------
void PlayerAudio::setspeed(double speed)
{
    if (resampleSource != nullptr) {
        resampleSource->setResamplingRatio(speed);
    }
}
//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------
double PlayerAudio::getspeed() const
{
    if (resampleSource)
        return resampleSource->getResamplingRatio();
    return 1.0;
}


#include "PlayerAudio.h"


PlayerAudio::PlayerAudio()
{
    formatManager.registerBasicFormats();
}

PlayerAudio::~PlayerAudio()
{
}

void PlayerAudio::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void PlayerAudio::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    transportSource.getNextAudioBlock(bufferToFill);

    if (isLooping && isMarker_A && isMarker_B)
    {
        if (transportSource.getCurrentPosition() >= setB)
        {
            transportSource.setPosition(setA);
            transportSource.start();
        }
    }
    else if (isLooping && transportSource.getCurrentPosition() >= transportSource.getLengthInSeconds())
    {
        transportSource.setPosition(0.0);
        transportSource.start();
    }
}

void PlayerAudio::releaseResources()
{
    transportSource.releaseResources();
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
            readerSource = std::make_unique<juce::AudioFormatReaderSource>(reader, true);

            // Attach safely
            transportSource.setSource(readerSource.get(),
                0,
                nullptr,
                reader->sampleRate);
            transportSource.start();
        }
    }
    resetMarkers();
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

void PlayerAudio::setGain(float gain)
{
    lastGain = gain;
    if (!muted)
        transportSource.setGain(gain);
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

void PlayerAudio::goToEnd()
{
    if (readerSource != nullptr && readerSource->getAudioFormatReader() != nullptr)
    {
        auto* reader = readerSource->getAudioFormatReader();
        double length = reader->lengthInSamples / reader->sampleRate;
        transportSource.setPosition(length - 0.1);
    }
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

void PlayerAudio::setLooping(bool willLoop)
{
    isLooping = willLoop;
}

void PlayerAudio::setmarkerA(double position)
{
    setA = position;
    isMarker_A = true;
    a_bLooping = true;
}

void PlayerAudio::setmarkerB(double position)
{
    setB = position;
    isMarker_B = true;
}

void PlayerAudio::resetMarkers()
{
    setA = 0.0;
    setB = 0.0;
    isMarker_A = false;
    isMarker_B = false;
}

void PlayerAudio::jumpForward(double seconds)
{
    double current = transportSource.getCurrentPosition();
    double target = current + seconds;

    if (isMarker_A && isMarker_B)
    {
        if (target > setB) target = setB;
        if (target < setA) target = setA;
    }
    else
    {
        if (target > transportSource.getLengthInSeconds()) target = transportSource.getLengthInSeconds();
        if (target < 0) target = 0;
    }
    transportSource.setPosition(target);
}

void PlayerAudio::jumpBackward(double seconds)
{
    double current = transportSource.getCurrentPosition();
    double target = current - seconds;

    if (isMarker_A && isMarker_B)
    {
        if (target < setA) target = setA;
        if (target > setB) target = setB;
    }
    else
    {
        if (target < 0) target = 0;     
        if (target > transportSource.getLengthInSeconds()) target = transportSource.getLengthInSeconds();
    }
    transportSource.setPosition(target);
}











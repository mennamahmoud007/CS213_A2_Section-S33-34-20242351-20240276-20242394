#include "PlayerAudio.h"

PlayerAudio::PlayerAudio()
{
    formatManager.registerBasicFormats();
}

PlayerAudio::~PlayerAudio() {}

void PlayerAudio::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void PlayerAudio::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    transportSource.getNextAudioBlock(bufferToFill);

    if (looping && transportSource.getCurrentPosition() >= transportSource.getLengthInSeconds())
    {
        transportSource.setPosition(0.0);
        transportSource.start();
    }
}

void PlayerAudio::releaseResources()
{
    transportSource.releaseResources();
}

bool PlayerAudio::loadFile(const juce::File& file)
{
    if (!file.existsAsFile()) return false;

    if (auto* reader = formatManager.createReaderFor(file))
    {
        transportSource.stop();
        transportSource.setSource(nullptr);
        readerSource.reset();

        readerSource = std::make_unique<juce::AudioFormatReaderSource>(reader, true);
        transportSource.setSource(readerSource.get(), 0, nullptr, reader->sampleRate);
        transportSource.start();
        return true;
    }
    return false;
}

void PlayerAudio::start() { transportSource.start(); }
void PlayerAudio::stop() { transportSource.stop(); }

void PlayerAudio::setGain(float gain)
{
    lastGain = gain;
    if (!muted)
        transportSource.setGain(gain);
}

void PlayerAudio::setPosition(double pos) { transportSource.setPosition(pos); }
double PlayerAudio::getPosition() const { return transportSource.getCurrentPosition(); }
double PlayerAudio::getLength() const { return transportSource.getLengthInSeconds(); }

void PlayerAudio::setLooping(bool shouldLoop) { looping = shouldLoop; }

void PlayerAudio::mute(bool shouldMute)
{
    muted = shouldMute;
    transportSource.setGain(muted ? 0.0f : lastGain);
}

bool PlayerAudio::isMuted() const { return muted; }












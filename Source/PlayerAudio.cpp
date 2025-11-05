#include "PlayerAudio.h"


PlayerAudio::PlayerAudio()
{
    formatManager.registerBasicFormats();
    resampleSource = std::make_unique<juce::ResamplingAudioSource>(&transportSource, false, 2);

}

PlayerAudio::~PlayerAudio()
{
}

void PlayerAudio::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    currentSampleRate = sampleRate;
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource->prepareToPlay(samplesPerBlockExpected, sampleRate);

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
        currentFile = file;

        if (auto* reader = formatManager.createReaderFor(file))
        {
            // ?? Disconnect old source first
            transportSource.stop();
            transportSource.setSource(nullptr);
            readerSource.reset();

            // Create new reader source
            std::unique_ptr<juce::AudioFormatReaderSource> newSource(new juce::AudioFormatReaderSource(reader, true));
            transportSource.setSource(newSource.get(), 0, nullptr, 44100.0);
            readerSource.reset(newSource.release());

            transportSource.start();
        }
        resetMarkers();
    }
    return true;
}


void PlayerAudio::start()
{
    transportSource.start();
}

void PlayerAudio::stop()
{
    fadingOut = true;
}

void PlayerAudio::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{

    resampleSource->getNextAudioBlock(bufferToFill);

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

    if (fadingOut)
    {
        float g = transportSource.getGain() - 0.05f;
        if (g <= 0.0f)
        {
            transportSource.setGain(0.0f);
            transportSource.stop();
            fadingOut = false;
        }
        else
        {
            transportSource.setGain(g);
        }
    }

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

void PlayerAudio::setspeed(double speed)
{
    if (resampleSource != nullptr) {
        resampleSource->setResamplingRatio(speed);
    }
}

double PlayerAudio::getspeed() const
{
    if (resampleSource)
        return resampleSource->getResamplingRatio();
    return 1.0;
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

void PlayerAudio::saveSession()
{

    juce::File sessionFile = juce::File::getSpecialLocation(juce::File::userDocumentsDirectory)
        .getChildFile("session.txt");

    double position = transportSource.getCurrentPosition();

    juce::String filePath = currentFile.existsAsFile() ? currentFile.getFullPathName() : "";

    juce::String content = filePath + "\n" + juce::String(position);
    sessionFile.replaceWithText(content);
}

void PlayerAudio::loadSession()
{

    juce::File sessionFile = juce::File::getSpecialLocation(juce::File::userDocumentsDirectory)
        .getChildFile("session.txt");

    if (sessionFile.existsAsFile())
    {
        juce::StringArray lines;
        sessionFile.readLines(lines);

        if (lines.size() >= 2)
        {
            juce::File lastFile(lines[0]);
            double lastPosition = lines[1].getDoubleValue();

            if (lastFile.existsAsFile())
            {
                LoadFile(lastFile);
                transportSource.setPosition(lastPosition);
            }
        }
    }
}
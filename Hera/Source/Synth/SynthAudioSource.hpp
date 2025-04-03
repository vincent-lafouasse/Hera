#pragma once

#include "JuceHeader.h"

class SynthAudioSource final : public juce::AudioSource {
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void releaseResources() override;
    void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;
};
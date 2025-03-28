#pragma once

#include "JuceHeader.h"

//==============================================================================
class MainContentComponent : public juce::AudioAppComponent {
   public:
    MainContentComponent() {
        setSize(800, 600);
        setAudioChannels(0, 2);  // no inputs, two outputs
    }

    ~MainContentComponent() override { shutdownAudio(); }

    void prepareToPlay(int samplesPerBlockExpected,
                       double sampleRate) override {
        juce::String message;
        message << "Preparing to play audio...\n";
        message << " samplesPerBlockExpected = " << samplesPerBlockExpected
                << "\n";
        message << " sampleRate = " << sampleRate;
        juce::Logger::getCurrentLogger()->writeToLog(message);
    }

    void releaseResources() override {
        juce::Logger::getCurrentLogger()->writeToLog(
            "Releasing audio resources");
    }

    void getNextAudioBlock(
        const juce::AudioSourceChannelInfo& bufferToFill) override {
        for (auto channel = 0; channel < bufferToFill.buffer->getNumChannels();
             ++channel) {
            // Get a pointer to the start sample in the buffer for this audio
            // output channel
            auto* buffer = bufferToFill.buffer->getWritePointer(
                channel, bufferToFill.startSample);

            // Fill the required number of samples with noise between -0.125 and
            // +0.125
            for (auto sample = 0; sample < bufferToFill.numSamples; ++sample)
                buffer[sample] = random.nextFloat() * 0.25f - 0.125f;
        }
    }

   private:
    juce::Random random;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainContentComponent)
};

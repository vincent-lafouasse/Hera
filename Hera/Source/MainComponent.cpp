#include "MainComponent.hpp"

MainComponent::MainComponent() {
    setSize(800, 600);
    setAudioChannels(0, 2);  // no inputs, two outputs
}

MainComponent::~MainComponent() {
    shutdownAudio();
}

void MainComponent::prepareToPlay(int samplesPerBlockExpected,
                                  double sampleRate) {
    // we dont allocate anything so let's just log some info
    juce::String message;
    message << "Preparing to play audio...\n";
    message << " samplesPerBlockExpected = " << samplesPerBlockExpected << "\n";
    message << " sampleRate = " << sampleRate;
    juce::Logger::writeToLog(message);
}

void MainComponent::releaseResources() {
    // there's nothing to release so let's just say goodbye
    juce::Logger::writeToLog("Releasing audio resources");
}

void MainComponent::getNextAudioBlock(
    const juce::AudioSourceChannelInfo& bufferToFill) {
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

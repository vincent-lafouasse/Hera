#include "MainComponent.hpp"

MainContentComponent::MainContentComponent() {
    setSize(800, 600);
    setAudioChannels(0, 2);  // no inputs, two outputs
}

MainContentComponent::~MainContentComponent() { shutdownAudio(); }

void MainContentComponent::prepareToPlay(int samplesPerBlockExpected,
                                         double sampleRate) {
    juce::String message;
    message << "Preparing to play audio...\n";
    message << " samplesPerBlockExpected = " << samplesPerBlockExpected
        << "\n";
    message << " sampleRate = " << sampleRate;
    juce::Logger::getCurrentLogger()->writeToLog(message);
}

void MainContentComponent::releaseResources() {
    juce::Logger::getCurrentLogger()->writeToLog(
        "Releasing audio resources");
}

void MainContentComponent::getNextAudioBlock(
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

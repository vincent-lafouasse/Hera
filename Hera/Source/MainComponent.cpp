#include "MainComponent.hpp"

MainComponent::MainComponent()
    : volume_knob(Slider::SliderStyle::RotaryHorizontalVerticalDrag,
                    Slider::TextEntryBoxPosition::TextBoxAbove) {
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
    const auto volume = static_cast<float>(volume_knob.getValue());

    for (auto channel = 0; channel < bufferToFill.buffer->getNumChannels();
         ++channel) {
        auto* buffer = bufferToFill.buffer->getWritePointer(
            channel, bufferToFill.startSample);

        constexpr float noise_volume = 0.1f;
        for (auto sample = 0; sample < bufferToFill.numSamples; ++sample) {
            auto noise = noise_volume * (2 * random.nextFloat() + 1);
            buffer[sample] = volume * noise;
        }
    }
}

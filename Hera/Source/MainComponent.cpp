#include "MainComponent.hpp"

MainComponent::MainComponent()
    : volume_knob(Slider::SliderStyle::RotaryHorizontalVerticalDrag,
                  Slider::TextEntryBoxPosition::TextBoxAbove) {
    setSize(800, 600);
    setAudioChannels(0, 2);  // no inputs, two outputs

    addAndMakeVisible(volume_knob);
    volume_knob.setRange(0.0, 1.0);
    volume_knob.setValue(0.5);
    volume_knob.addListener(this);
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

void MainComponent::sliderValueChanged(juce::Slider* slider) {
    if (slider == &volume_knob) {
        volume_knob.setValue(slider->getValue());
    }
}

void MainComponent::resized() {
    auto sliderLeft = 120;
    volume_knob.setBounds(sliderLeft, 20, getWidth() - sliderLeft - 10, 20);
}

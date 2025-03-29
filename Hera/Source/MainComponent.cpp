#include "MainComponent.hpp"

MainComponent::MainComponent()
    : volume(0.5),
      volume_knob(Slider::SliderStyle::RotaryHorizontalVerticalDrag,
                  Slider::TextEntryBoxPosition::TextBoxAbove),
      volume_smoother(0.9f, 0.1f) {
    setSize(400, 300);
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
    this->volume_smoother.setTarget(this->volume.load());

    for (auto channel = 0; channel < bufferToFill.buffer->getNumChannels();
         ++channel) {
        auto* buffer = bufferToFill.buffer->getWritePointer(
            channel, bufferToFill.startSample);

        for (auto sample = 0; sample < bufferToFill.numSamples; ++sample) {
            constexpr float noise_volume = 0.1f;
            auto noise = noise_volume * (2 * random.nextFloat() + 1);

            const float sample_volume = volume_smoother.get(channel);
            buffer[sample] = sample_volume * noise;
        }
    }
}

void MainComponent::sliderValueChanged(juce::Slider* slider) {
    if (slider == &volume_knob) {
        volume.store(static_cast<float>(slider->getValue()));
    }
}

void MainComponent::resized() {
    volume_knob.setBounds(0, 0, 100, 100);
}

#pragma once

#include "JuceHeader.h"

#include "Integrator.hpp"

#include <array>

class MainComponent final : public juce::AudioAppComponent,
                            public juce::Slider::Listener {
   public:
    MainComponent();
    ~MainComponent() override;

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void releaseResources() override;
    void getNextAudioBlock(
        const juce::AudioSourceChannelInfo& bufferToFill) override;

    void resized() override;

    void sliderValueChanged(juce::Slider* slider) override;

    void set_frequency(double freq);

   private:
    void advance_phase(std::size_t channel);

    double frequency;
    std::array<double, 2> oscillator_phase{};
    double oscillator_phase_increment{};
    double sample_rate{};

    std::atomic<float> volume;
    juce::Slider volume_knob;
    Integrator<2, float> volume_smoother;

    juce::Random random;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};

#pragma once

#include "JuceHeader.h"

#include "StereoIntegrator.hpp"

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

   private:
    juce::Random random;

    std::atomic<float> volume;
    juce::Slider volume_knob;
    StereoIntegrator volume_smoother;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};

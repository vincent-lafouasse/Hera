#pragma once

#include "JuceHeader.h"

class MainComponent : public juce::AudioAppComponent {
   public:
    MainComponent();
    ~MainComponent() override;

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void releaseResources() override;
    void getNextAudioBlock(
        const juce::AudioSourceChannelInfo& bufferToFill) override;

   private:
    juce::Random random;
    juce::Slider volume_slider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};

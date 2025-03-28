#pragma once

#include "JuceHeader.h"

class MainContentComponent : public juce::AudioAppComponent {
   public:
    MainContentComponent();
    ~MainContentComponent() override;

    void prepareToPlay(int samplesPerBlockExpected,
                       double sampleRate) override;
    void releaseResources() override;
    void getNextAudioBlock(
        const juce::AudioSourceChannelInfo& bufferToFill) override;

   private:
    juce::Random random;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainContentComponent)
};

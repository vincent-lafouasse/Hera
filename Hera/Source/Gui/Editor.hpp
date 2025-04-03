#pragma once

#include "Processor.hpp"
#include "JuceHeader.h"

//==============================================================================

class VolumeKnob final : public juce::Slider {
   public:
    juce::String getTextFromValue(double value) override;
};

//==============================================================================
/**
 */
class HeraEditor final : public juce::AudioProcessorEditor {
   public:
    explicit HeraEditor(HeraProcessor&);
    ~HeraEditor() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;

   private:
    void setupGainKnob();

   private:
    HeraProcessor& audioProcessor;

    VolumeKnob volume_knob;
    juce::Label volume_label;

   public:
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
        volume_attachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(HeraEditor)
};
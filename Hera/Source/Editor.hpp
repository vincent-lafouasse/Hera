#pragma once

#include "Processor.hpp"

//==============================================================================

class VolumeKnob : public juce::Slider {
   public:
    juce::String getTextFromValue(double value) override;
};

//==============================================================================
/**
 */
class HeraEditor : public juce::AudioProcessorEditor,
                   public juce::Slider::Listener {
   public:
    explicit HeraEditor(HeraProcessor&);
    ~HeraEditor() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(juce::Slider* slider) override;

   private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    HeraProcessor& audioProcessor;

    VolumeKnob volume_knob;
    juce::Label volume_label;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(HeraEditor)
};

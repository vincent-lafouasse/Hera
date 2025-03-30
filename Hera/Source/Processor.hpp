#pragma once

#include "Integrator.hpp"
#include "JuceHeader.h"

//==============================================================================
/**
 */
class HeraProcessor final : public juce::AudioProcessor
#if JucePlugin_Enable_ARA
    ,
                            public juce::AudioProcessorARAExtension
#endif
{
   public:
    //==============================================================================
    HeraProcessor();
    ~HeraProcessor() override;

    //==============================================================================
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
#endif

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void changeProgramName(int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;
    //==============================================================================

    std::atomic<float> volume;

   private:
    Integrator<1, float> volume_smoother;

    float frequency{};
    float phase{};
    float phase_increment{};
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(HeraProcessor)
};

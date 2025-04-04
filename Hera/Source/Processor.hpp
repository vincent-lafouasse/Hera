#pragma once

#include "Integrator.hpp"
#include "JuceHeader.h"
#include "Synth/AudioSource.hpp"

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

    void set_frequency(float freq);

    static AudioProcessorValueTreeState::ParameterLayout
    createParameterLayout();
    juce::AudioProcessorValueTreeState params;

    juce::MidiKeyboardState keyboardState{};

   private:
    SynthAudioSource synthSource;

   public:
    static const std::string volume_id;
    static const std::string volume_name;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(HeraProcessor)
};

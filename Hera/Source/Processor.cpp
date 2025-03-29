/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "Processor.hpp"
#include "Editor.hpp"
#include "Integrator.hpp"

//==============================================================================
HeraProcessor::HeraProcessor()
    : AudioProcessor(
          BusesProperties().withOutput("Output",
                                       juce::AudioChannelSet::stereo(),
                                       true))

      ,
      volume(0),
      volume_smoother(0.1f, 0.9f) {}

HeraProcessor::~HeraProcessor() = default;

void HeraProcessor::processBlock(juce::AudioBuffer<float>& buffer,
                                 juce::MidiBuffer&) {
    const auto nChannels = static_cast<size_t>(getTotalNumOutputChannels());

    volume_smoother.setTarget(volume.load());

    for (size_t channel = 0; channel < nChannels; ++channel) {
        auto* channelData = buffer.getWritePointer(static_cast<int>(channel));
        const auto bufferSize = static_cast<size_t>(buffer.getNumSamples());

        for (size_t sample = 0; sample < bufferSize; sample++) {
            constexpr float noise_amplitude = 0.1f;
            const float noise =
                noise_amplitude * (2.0f * random.nextFloat() - 1.0f);
            channelData[sample] = volume_smoother.get(channel) * noise;
        }
    }
}

void HeraProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) {
    // not much to do here so let's say hi
    juce::String message;
    message << "Preparing to play audio...\n";
    message << " samplesPerBlockExpected = " << samplesPerBlock << "\n";
    message << " sampleRate = " << sampleRate;
    juce::Logger::writeToLog(message);
}

void HeraProcessor::releaseResources() {
    juce::Logger::writeToLog("Releasing audio resources");
}

//================== boiler plate =============================================

const juce::String HeraProcessor::getName() const {
    return JucePlugin_Name;
}

bool HeraProcessor::acceptsMidi() const {
    return true;
}

bool HeraProcessor::producesMidi() const {
    return false;
}

bool HeraProcessor::isMidiEffect() const {
    return false;
}

double HeraProcessor::getTailLengthSeconds() const {
    return 0.0;
}

int HeraProcessor::getNumPrograms() {
    return 1;  // NB: some hosts don't cope very well if you tell them there are
               // 0 programs, so this should be at least 1, even if you're not
               // really implementing programs.
}

int HeraProcessor::getCurrentProgram() {
    return 0;
}

void HeraProcessor::setCurrentProgram(int index) {
    (void)index;
}

const juce::String HeraProcessor::getProgramName(int index) {
    (void)index;
    return "Hera";
}

void HeraProcessor::changeProgramName(int index, const juce::String& newName) {
    (void)index;
    (void)newName;
}

//==============================================================================

#ifndef JucePlugin_PreferredChannelConfigurations
bool HeraProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const {
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused(layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono() &&
        layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
#if !JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
#endif
}
#endif

//==============================================================================

bool HeraProcessor::hasEditor() const {
    return true;  // (change this to false if you choose to not supply an
                  // editor)
}

juce::AudioProcessorEditor* HeraProcessor::createEditor() {
    return new HeraEditor(*this);
}

//==============================================================================
void HeraProcessor::getStateInformation(juce::MemoryBlock& destData) {
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    (void)destData;
}

void HeraProcessor::setStateInformation(const void* data, int sizeInBytes) {
    // You should use this method to restore your parameters from this memory
    // block, whose contents will have been created by the getStateInformation()
    // call.
    (void)data;
    (void)sizeInBytes;
}

//==============================================================================
// This creates new instances of the plugin...
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
    return new HeraProcessor();
}

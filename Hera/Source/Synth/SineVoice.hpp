#pragma once

#include <JuceHeader.h>

class SineVoice final : juce::SynthesiserSound {
    bool appliesToNote(int) override { return true; }
    bool appliesToChannel(int) override { return true; }
    ~SineVoice() = default;
};
#pragma once

#include <JuceHeader.h>

class SineSound final : juce::SynthesiserSound {
    bool appliesToNote(int) override { return true; }
    bool appliesToChannel(int) override { return true; }
    ~SineSound() override = default;
};
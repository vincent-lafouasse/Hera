#pragma once

#include "JuceHeader.h"
#include "SineSound.hpp"

class SineVoice final: public juce::SynthesiserVoice {
    bool canPlaySound(juce::SynthesiserSound* sound) override {
        return dynamic_cast<SineSound*>(sound) != nullptr;
    }

    void startNote(int, float, juce::SynthesiserSound*, int) override {}
};
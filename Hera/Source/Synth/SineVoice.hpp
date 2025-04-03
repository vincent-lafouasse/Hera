#pragma once

#include "JuceHeader.h"
#include "SineSound.hpp"

class SineVoice final : public juce::SynthesiserVoice {
    void renderNextBlock(AudioBuffer<float>& outputBuffer,
                         int startSample,
                         int numSamples) override;

    void startNote(int, float, juce::SynthesiserSound*, int) override;
    void stopNote(float velocity, bool allowTailOff) override;

    void pitchWheelMoved(int newPitchWheelValue) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;

    bool canPlaySound(juce::SynthesiserSound* sound) override;
};
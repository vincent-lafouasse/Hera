#include "SineVoice.hpp"

#include "SineSound.hpp"

void SineVoice::renderNextBlock(AudioBuffer<float>& outputBuffer,
                                int startSample,
                                int numSamples) {}

void SineVoice::startNote(int midiNote,
                          float velocity,
                          juce::SynthesiserSound* sound,
                          int /*pitchWheelPosition*/) {
    this->phase = 0.0f;
    this->level = 0.15 * velocity;
    this->tailOff = 0.0;

    const double frequency =
        440.0 * powf(2.0, static_cast<float>(midiNote - 69) / 12.0);
    this->phaseIncrement =
        frequency * juce::MathConstants<float>::twoPi / getSampleRate();
}

void SineVoice::stopNote(float velocity, bool allowTailOff) {}

void SineVoice::pitchWheelMoved(int newPitchWheelValue) {
    (void)newPitchWheelValue;
}
void SineVoice::controllerMoved(int controllerNumber, int newControllerValue) {
    (void)controllerNumber;
    (void)newControllerValue;
}

bool SineVoice::canPlaySound(juce::SynthesiserSound* sound) {
    return dynamic_cast<SineSound*>(sound) != nullptr;
}
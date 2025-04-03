#include "SineVoice.hpp"

#include "SineSound.hpp"

void SineVoice::renderNextBlock(AudioBuffer<float>& outputBuffer,
                                const int startSample,
                                const int numSamples) {}

void SineVoice::startNote(const int midiNote,
                          const float velocity,
                          juce::SynthesiserSound* sound,
                          const int /*pitchWheelPosition*/) {
    this->phase = 0.0f;
    this->level = 0.15 * velocity;
    this->tailOff = 0.0;

    const double frequency =
        440.0 * powf(2.0, static_cast<float>(midiNote - 69) / 12.0);
    this->phaseIncrement =
        frequency * juce::MathConstants<float>::twoPi / getSampleRate();
}

void SineVoice::stopNote(const float velocity, const bool allowTailOff) {}

void SineVoice::pitchWheelMoved(const int newPitchWheelValue) {
    (void)newPitchWheelValue;
}
void SineVoice::controllerMoved(const int controllerNumber,
                                int const newControllerValue) {
    (void)controllerNumber;
    (void)newControllerValue;
}

bool SineVoice::canPlaySound(juce::SynthesiserSound* sound) {
    return dynamic_cast<SineSound*>(sound) != nullptr;
}
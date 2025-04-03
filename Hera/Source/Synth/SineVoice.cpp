#include "SineVoice.hpp"

void SineVoice::renderNextBlock(AudioBuffer<float>& outputBuffer,
                                int startSample,
                                int numSamples) {}

void SineVoice::startNote(int, float, juce::SynthesiserSound*, int) {}
void SineVoice::stopNote(float velocity, bool allowTailOff) {}

void SineVoice::pitchWheelMoved(int newPitchWheelValue) {}
void SineVoice::controllerMoved(int controllerNumber, int newControllerValue) {}

bool SineVoice::canPlaySound(juce::SynthesiserSound* sound) {
    return dynamic_cast<SineSound*>(sound) != nullptr;
}
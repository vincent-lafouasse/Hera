#include "SynthAudioSource.hpp"

#include "SineSound.hpp"
#include "SineVoice.hpp"

void SynthAudioSource::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {
    (void)samplesPerBlockExpected;
    (void)sampleRate;
}

void SynthAudioSource::releaseResources() {}

void SynthAudioSource::getNextAudioBlock(const AudioSourceChannelInfo &bufferToFill) {
    (void)bufferToFill;
}

#include "AudioSource.hpp"

#include "Voice.hpp"

void SynthAudioSource::prepareToPlay(int samplesPerBlockExpected,
                                     double sampleRate) {
    (void)samplesPerBlockExpected;
    (void)sampleRate;
}

void SynthAudioSource::releaseResources() {}

void SynthAudioSource::getNextAudioBlock(
    const AudioSourceChannelInfo& bufferToFill) {
    (void)bufferToFill;
}

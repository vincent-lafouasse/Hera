#include "SineVoice.hpp"

namespace {
template <typename NumericType>
void wrapping_add(NumericType& value, NumericType addend, NumericType limit) {
    value += addend;
    while (value >= limit) {
        value -= limit;
    }
}
}  // namespace

void SineVoice::renderNextBlock(AudioBuffer<float>& outputBuffer,
                                const int startSample,
                                const int numSamples) {
    if (this->phaseIncrement == 0.0)
        return;

    const auto nChannels = outputBuffer.getNumChannels();

    if (this->tailOff != 0.0) {
        // decaying
        for (int i = 0; i < numSamples; i++) {
            const float sine = static_cast<float>(this->tailOff * this->level *
                                                  std::sin(this->phase));
            wrapping_add(this->phase, this->phaseIncrement,
                         juce::MathConstants<double>::twoPi);

            for (auto channel = 0; channel < nChannels; ++channel) {
                outputBuffer.addSample(channel, startSample + i, sine);
            }

            this->tailOff *= 0.99;  // exponential decay

            if (this->tailOff < 0.05) {
                this->clearCurrentNote();
                this->phaseIncrement = 0.0;
                return;
            }
        }
    } else {
        // regular buffer
        for (int i = 0; i < numSamples; i++) {
            const float sine =
                static_cast<float>(this->level * std::sin(this->phase));
            wrapping_add(this->phase, this->phaseIncrement,
                         juce::MathConstants<double>::twoPi);

            for (auto channel = 0; channel < nChannels; ++channel) {
                outputBuffer.addSample(channel, startSample + i, sine);
            }
        }
    }
}

void SineVoice::startNote(const int midiNote,
                          const float velocity,
                          juce::SynthesiserSound* sound,
                          const int /*pitchWheelPosition*/) {
    (void)sound;

    this->phase = 0.0f;
    this->level = 0.15 * velocity;
    this->tailOff = 0.0;

    const double frequency =
        440.0 * powf(2.0, static_cast<float>(midiNote - 69) / 12.0f);
    this->phaseIncrement =
        frequency * juce::MathConstants<float>::twoPi / getSampleRate();
}

void SineVoice::stopNote(const float velocity, const bool allowTailOff) {
    (void)velocity;

    if (allowTailOff) {
        if (this->tailOff == 0.0) {
            this->tailOff = 1.0;
        }
    } else {
        this->clearCurrentNote();
        this->phaseIncrement = 0.0;
    }
}

void SineVoice::pitchWheelMoved(const int newPitchWheelValue) {
    (void)newPitchWheelValue;
}
void SineVoice::controllerMoved(const int controllerNumber,
                                int const newControllerValue) {
    (void)controllerNumber;
    (void)newControllerValue;
}

bool SineVoice::canPlaySound(juce::SynthesiserSound* sound) {
    return dynamic_cast<SynthSound*>(sound) != nullptr;
}
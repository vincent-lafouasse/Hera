#include "Editor.hpp"
#include <iomanip>
#include <sstream>
#include "Processor.hpp"

namespace {
constexpr int windowWidth = 1600;
constexpr int windowHeight = 400;

constexpr int volumeKnobSize = 100;

constexpr int margin = 15;
}  // namespace

//==============================================================================
HeraEditor::HeraEditor(HeraProcessor& p)
    : AudioProcessorEditor(&p),
      audioProcessor(p),
      keyboardComponent(p.keyboardState,
                        KeyboardComponentBase::horizontalKeyboard) {
    setSize(windowWidth, windowHeight);

    this->setupKeyboard();
    this->setupGainKnob();
}

HeraEditor::~HeraEditor() = default;

void HeraEditor::setupKeyboard() {}

void HeraEditor::setupGainKnob() {
    this->volume_attachment =
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
            audioProcessor.params, HeraProcessor::volume_id, this->volume_knob);

    addAndMakeVisible(volume_knob);
    volume_knob.setSliderStyle(
        juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    constexpr int value_textbox_width = 100;
    constexpr int value_textbox_height = 25;
    volume_knob.setTextBoxStyle(
        juce::Slider::TextEntryBoxPosition::TextBoxBelow, true,
        value_textbox_width, value_textbox_height);

    volume_knob.setDoubleClickReturnValue(true, 0.5);

    addAndMakeVisible(volume_label);
    volume_label.setText("Volume", juce::dontSendNotification);
    volume_label.attachToComponent(&volume_knob, true);
}

void HeraEditor::resized() {
    volume_knob.setBounds(margin, (windowHeight - volumeKnobSize) / 2,
                          volumeKnobSize, volumeKnobSize);
}

juce::String VolumeKnob::getTextFromValue(const double value) {
    std::stringstream ss{};
    ss << std::fixed;
    ss << std::setprecision(1);
    ss << 10.0 * value;
    return ss.str();
}

//==============================================================================
void HeraEditor::paint(juce::Graphics& g) {
    // (Our component is opaque, so we must completely fill the background with
    // a solid colour)
    g.fillAll(
        getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}
#include "Editor.hpp"
#include <iomanip>
#include <sstream>
#include "Processor.hpp"

namespace {
constexpr int windowWidth = 1600;
constexpr int windowHeight = 400;
}  // namespace

//==============================================================================
HeraEditor::HeraEditor(HeraProcessor& p)
    : AudioProcessorEditor(&p),
      audioProcessor(p),
      volume_label("VolumeLabel", "Volume"),
      keyboardComponent(p.keyboardState,
                        KeyboardComponentBase::horizontalKeyboard) {
    setSize(windowWidth, windowHeight);

    this->setupKeyboard();
    this->setupGainKnob();
}

HeraEditor::~HeraEditor() = default;

void HeraEditor::setupKeyboard() {
    addAndMakeVisible (keyboardComponent);
}

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
    volume_label.setColour (juce::Label::textColourId, juce::Colours::lightgreen);
    volume_label.setJustificationType (juce::Justification::centred);


    volume_label.attachToComponent(&volume_knob, true);
}

void HeraEditor::resized() {
    constexpr float volumeKnobSize = 0.15;
    constexpr float margin = 0.05f;
    volume_knob.setBoundsRelative(margin, 0.5 * (1.0 - volumeKnobSize),
                                  volumeKnobSize, volumeKnobSize);

    constexpr float keyboardWidth = 1.0 - 3.0 * margin - volumeKnobSize;
    keyboardComponent.setBoundsRelative(2.0 * margin + volumeKnobSize, margin,
                                        keyboardWidth, 1.0 - 2.0 * margin);
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
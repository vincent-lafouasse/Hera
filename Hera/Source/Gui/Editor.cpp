#include "Editor.hpp"
#include <iomanip>
#include <sstream>
#include "Processor.hpp"

namespace {
constexpr float aspectRatio = 6.4;
constexpr int screenWidth = 1000;
constexpr int screenHeight = static_cast<int>(screenWidth / aspectRatio);
}  // namespace

//==============================================================================
HeraEditor::HeraEditor(HeraProcessor& p)
    : AudioProcessorEditor(&p),
      audioProcessor(p),
      volume_label("VolumeLabel", "Volume"),
      keyboardComponent(p.keyboardState,
                        KeyboardComponentBase::horizontalKeyboard) {
    setSize(screenWidth, screenHeight);

    this->setupKeyboard();
    this->setupGainKnob();
}

HeraEditor::~HeraEditor() = default;

void HeraEditor::setupKeyboard() {
    addAndMakeVisible(keyboardComponent);
    keyboardComponent.setBlackNoteLengthProportion(0.6);

    constexpr int c1 = 24;
    constexpr int c6 = 84;
    keyboardComponent.setAvailableRange(c1, c6);
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
    volume_label.setColour(juce::Label::textColourId,
                           juce::Colours::lightgreen);
    volume_label.setJustificationType(juce::Justification::centred);

    volume_label.attachToComponent(&volume_knob, true);
}

void HeraEditor::resized() {
    juce::Rectangle<int> area = getLocalBounds();

    constexpr int componentHeight = static_cast<int>(screenHeight * 0.90);
    constexpr int volumeSectionWidth = static_cast<int>(screenWidth * 0.15);
    constexpr int keyboardSectionWidth = static_cast<int>(screenWidth * 0.85);

    volume_knob.setBounds(
        area.removeFromLeft(volumeSectionWidth).removeFromTop(componentHeight));
    keyboardComponent.setBounds(area.removeFromLeft(keyboardSectionWidth)
                                    .removeFromTop(componentHeight));
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
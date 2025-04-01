#include "Editor.hpp"
#include <iomanip>
#include <sstream>
#include "Processor.hpp"

//==============================================================================
HeraEditor::HeraEditor(HeraProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p) {
    constexpr int width = 200;
    constexpr int height = 400;
    setSize(width, height);

    addAndMakeVisible(volume_knob);
    volume_knob.setSliderStyle(
        juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    constexpr int value_textbox_width = 100;
    constexpr int value_textbox_height = 25;
    volume_knob.setTextBoxStyle(
        juce::Slider::TextEntryBoxPosition::TextBoxBelow, true,
        value_textbox_width, value_textbox_height);

    volume_knob.setRange(0.0, 1.0);
    volume_knob.setValue(0.5);
    volume_knob.setDoubleClickReturnValue(true, 0.5);
    volume_knob.addListener(this);

    addAndMakeVisible(volume_label);
    volume_label.setText("Volume", juce::dontSendNotification);
    volume_label.attachToComponent(&volume_knob, true);
}

HeraEditor::~HeraEditor() = default;

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

void HeraEditor::resized() {
    volume_knob.setBounds(getLocalBounds());
}

void HeraEditor::sliderValueChanged(juce::Slider* slider) {
    if (slider == &volume_knob) {
        audioProcessor.set_volume(static_cast<float>(volume_knob.getValue()));
    }
}

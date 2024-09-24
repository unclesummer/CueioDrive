#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class CueioDriveAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    CueioDriveAudioProcessorEditor (CueioDriveAudioProcessor&);
    ~CueioDriveAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    CueioDriveAudioProcessor& audioProcessor;

    juce::Font customFont;

    juce::Slider driveKnob;
    juce::Slider rangeKnob;
    juce::Slider blendKnob;
    juce::Slider volumeKnob;

    juce::Label driveLabel;
    juce::Label rangeLabel;
    juce::Label blendLabel;
    juce::Label volumeLabel;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> driveAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> rangeAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> blendAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> volumeAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CueioDriveAudioProcessorEditor)
};
#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class CueioDriveAudioProcessor;  // Forward declaration


class CueioDriveAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    CueioDriveAudioProcessorEditor(CueioDriveAudioProcessor&);
    ~CueioDriveAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;


private:
    void initializeWebView(); // Declaração
    
    CueioDriveAudioProcessor& audioProcessor;
    
    void timerCallback();

    // WebBrowserComponent para carregar a aplicação React
    std::unique_ptr<juce::WebBrowserComponent> webView;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CueioDriveAudioProcessorEditor)
};

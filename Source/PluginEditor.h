#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class CustomLookAndFeel : public juce::LookAndFeel_V4
{
public:
    CustomLookAndFeel()
    {
        // Carregar a imagem do ponteiro do slider (substitua pelo seu arquivo de imagem)
        knobImage = juce::ImageFileFormat::loadFrom(BinaryData::knob_png, BinaryData::knob_pngSize);
    }

    void drawRotarySlider (juce::Graphics& g,
                            int x, int y, int width, int height,
                            float sliderPos,
                            float rotaryStartAngle,
                            float rotaryEndAngle,
                            juce::Slider& slider) override
    {
        auto radius = juce::jmin (width / 2, height / 2) - 4.0f; // Margem
        auto centreX = x + width * 0.5f;
        auto centreY = y + height * 0.5f;
        auto rx = radius * 0.5f;
        auto ry = radius * 0.5f;

        // Desenhar o fundo do slider
        g.setColour (slider.findColour (juce::Slider::backgroundColourId));
        g.fillEllipse (x, y, width, height);

        // Definir a cor do ponteiro
        g.setColour (slider.findColour (juce::Slider::thumbColourId));

        // Calcular a posição do ponteiro
        float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        juce::Point<float> thumbPoint (centreX + std::cos (angle) * rx,
                                        centreY + std::sin (angle) * ry);

        // Redimensionar a imagem do knob
        auto knobWidth = 60; // Largura do ponteiro do slider
        auto knobHeight = 60; // Altura do ponteiro do slider
        g.drawImage (knobImage, thumbPoint.x - knobWidth / 2, thumbPoint.y - knobHeight / 2, 
                     knobWidth, knobHeight, 0, 0, knobImage.getWidth(), knobImage.getHeight());
    }

private:
    juce::Image knobImage; // Imagem do ponteiro do slider
};

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
    juce::Image backgroundImage;

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

    std::unique_ptr<CustomLookAndFeel> customLookAndFeel; // Adicione esta linha

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CueioDriveAudioProcessorEditor)
};

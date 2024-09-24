#include "PluginProcessor.h"
#include "PluginEditor.h"

CueioDriveAudioProcessorEditor::CueioDriveAudioProcessorEditor (CueioDriveAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (400, 300);

    // Carregar a fonte personalizada (assumindo que MyFont.ttf foi adicionada)

    customFont = juce::Font(juce::Typeface::createSystemTypefaceFor(BinaryData::ABoxFor_ttf, BinaryData::ABoxFor_ttfSize));

    auto setupSlider = [this](juce::Slider& slider, juce::Label& label, const juce::String& paramID, const juce::String& labelText)
    {
        addAndMakeVisible(slider);
        slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
        slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
        slider.setPopupDisplayEnabled(true, false, this);

        addAndMakeVisible(label);
        label.setText(labelText, juce::dontSendNotification);
        label.attachToComponent(&slider, false);
        
        // Aplicar a fonte personalizada
        label.setFont(customFont.withHeight(29.0f)); // Ajuste a altura conforme necessário

        label.setVisible(true);
        driveLabel.setVisible(true);
        rangeLabel.setVisible(true);
        blendLabel.setVisible(true);
        volumeLabel.setVisible(true);

        return std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
            audioProcessor.parameters, paramID, slider);
    };

    driveAttachment = setupSlider(driveKnob, driveLabel, "drive", "Drive");
    rangeAttachment = setupSlider(rangeKnob, rangeLabel, "range", "Range");
    blendAttachment = setupSlider(blendKnob, blendLabel, "blend", "Blend");
    volumeAttachment = setupSlider(volumeKnob, volumeLabel, "volume", "Volume");


}

CueioDriveAudioProcessorEditor::~CueioDriveAudioProcessorEditor()
{
}

void CueioDriveAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void CueioDriveAudioProcessorEditor::resized()
{
    auto area = getLocalBounds();
    
    // Dimensões dos knobs e labels
    int knobWidth = 100;
    int knobHeight = 100;
    int labelHeight = 20;
    
    // Espaçamento entre os knobs
    int horizontalSpacing = 50; // Espaço entre as colunas de knobs
    int verticalSpacing = 40;   // Espaço entre as linhas de knobs e labels

    // Número de colunas e linhas (dois knobs por linha, dois por coluna)
    int numColumns = 2;
    int numRows = 2;
    
    // Largura total necessária para os dois knobs e o espaçamento horizontal
    int totalWidth = (numColumns * knobWidth) + ((numColumns - 1) * horizontalSpacing);

    // Altura total necessária para os dois knobs e o espaçamento vertical
    int totalHeight = (numRows * knobHeight) + ((numRows - 1) * verticalSpacing) + (numRows * labelHeight);

    // Calcular o ponto de início para centralizar a área dos knobs/labels
    auto startX = (area.getWidth() - totalWidth) / 2;
    auto startY = (area.getHeight() - totalHeight) / 2;

    // Posição da primeira linha de knobs (Drive e Range)
    driveKnob.setBounds(startX, startY + labelHeight, knobWidth, knobHeight);
    driveLabel.setBounds(driveKnob.getX(), driveKnob.getY() - labelHeight, knobWidth, labelHeight);

    rangeKnob.setBounds(startX + knobWidth + horizontalSpacing, startY + labelHeight, knobWidth, knobHeight);
    rangeLabel.setBounds(rangeKnob.getX(), rangeKnob.getY() - labelHeight, knobWidth, labelHeight);

    // Posição da segunda linha de knobs (Blend e Volume)
    blendKnob.setBounds(startX, startY + knobHeight + labelHeight + verticalSpacing + labelHeight, knobWidth, knobHeight);
    blendLabel.setBounds(blendKnob.getX(), blendKnob.getY() - labelHeight, knobWidth, labelHeight);

    volumeKnob.setBounds(startX + knobWidth + horizontalSpacing, blendKnob.getY(), knobWidth, knobHeight);
    volumeLabel.setBounds(volumeKnob.getX(), volumeKnob.getY() - labelHeight, knobWidth, labelHeight);
}

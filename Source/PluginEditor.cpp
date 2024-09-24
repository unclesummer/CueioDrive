#include "PluginProcessor.h"
#include "PluginEditor.h"

CueioDriveAudioProcessorEditor::CueioDriveAudioProcessorEditor (CueioDriveAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (400, 300);

    // Carregar a imagem de fundo (assumindo que background.png foi adicionada)
    backgroundImage = juce::ImageFileFormat::loadFrom(BinaryData::background_png, BinaryData::background_pngSize);
    
    // Carregar a fonte personalizada (assumindo que MyFont.ttf foi adicionada)
    customFont = juce::Font(juce::Typeface::createSystemTypefaceFor(BinaryData::ABoxFor_ttf, BinaryData::ABoxFor_ttfSize));

    // Criar uma instância do look and feel personalizado
    customLookAndFeel = std::make_unique<CustomLookAndFeel>();

    // Aplicar o LookAndFeel aos sliders
    driveKnob.setLookAndFeel(customLookAndFeel.get());
    rangeKnob.setLookAndFeel(customLookAndFeel.get());
    blendKnob.setLookAndFeel(customLookAndFeel.get());
    volumeKnob.setLookAndFeel(customLookAndFeel.get());

    auto setupSlider = [this](juce::Slider& slider, juce::Label& label, const juce::String& paramID, const juce::String& labelText)
    {
        addAndMakeVisible(slider);
        slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
        slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
        slider.setPopupDisplayEnabled(true, false, this);

        addAndMakeVisible(label);
        label.setText(labelText, juce::dontSendNotification);
        label.attachToComponent(&slider, false);

        // Definir a cor do texto da label como preto
        label.setColour(juce::Label::textColourId, juce::Colours::black);
        
        // Aplicar a fonte personalizada
        label.setFont(customFont.withHeight(29.0f)); // Ajuste a altura conforme necessário

        label.setVisible(true);
        driveLabel.setVisible(true);
        rangeLabel.setVisible(true);
        blendLabel.setVisible(true);
        volumeLabel.setVisible(true);

        return std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters, paramID, slider);
    };

    driveAttachment = setupSlider(driveKnob, driveLabel, "drive", "Drive");
    rangeAttachment = setupSlider(rangeKnob, rangeLabel, "range", "Range");
    blendAttachment = setupSlider(blendKnob, blendLabel, "blend", "Blend");
    volumeAttachment = setupSlider(volumeKnob, volumeLabel, "volume", "Volume");
}

CueioDriveAudioProcessorEditor::~CueioDriveAudioProcessorEditor()
{
    // Limpar LookAndFeel quando o editor for destruído
    driveKnob.setLookAndFeel(nullptr);
    rangeKnob.setLookAndFeel(nullptr);
    blendKnob.setLookAndFeel(nullptr);
    volumeKnob.setLookAndFeel(nullptr);
}

void CueioDriveAudioProcessorEditor::paint (juce::Graphics& g)
{
    // Primeiro, preencha o background com a cor branca
    g.fillAll(juce::Colours::white); 

    // Depois, desenhe a imagem de fundo
    if (!backgroundImage.isNull())
    {
        // Definir o tamanho desejado para a imagem
        int imageWidth = 80;  // Ajuste conforme necessário
        int imageHeight = 55; // Ajuste conforme necessário

        // Calcular a posição para colocar a imagem no canto inferior direito
        int startX = getWidth() - imageWidth;  // Alinhar à direita
        int startY = getHeight() - imageHeight; // Alinhar à parte inferior

        // Desenhar a imagem redimensionada no centro
        g.drawImage(backgroundImage, startX, startY, imageWidth, imageHeight, 0, 0, backgroundImage.getWidth(), backgroundImage.getHeight());
    }
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

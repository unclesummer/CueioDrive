#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================

CueioDriveAudioProcessorEditor::CueioDriveAudioProcessorEditor (CueioDriveAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p){
    initializeWebView(); // Inicializa o WebView
    setSize(600, 620); // Define o tamanho da interface
}

CueioDriveAudioProcessorEditor::~CueioDriveAudioProcessorEditor() {}

void CueioDriveAudioProcessorEditor::initializeWebView() {
    // Definindo uma pasta de dados personalizada para o WebView2
    auto userDataFolder = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userDocumentsDirectory)
                              .getChildFile("CueioDrive"); // Substitua pelo nome do seu plugin

    webView = std::make_unique<juce::WebBrowserComponent>(juce::WebBrowserComponent::Options{}
        .withBackend(juce::WebBrowserComponent::Options::Backend::webview2)
        .withWinWebView2Options(
            juce::WebBrowserComponent::Options::WinWebView2{}
                .withUserDataFolder(userDataFolder) // Usando a pasta de dados personalizada
                .withBackgroundColour(juce::Colours::white)));

    addAndMakeVisible(*webView);

    // Carregar o HTML
    auto file = juce::File::getCurrentWorkingDirectory().getChildFile("C:/Users/Geral/Documents/JUCE_tests/CueioDrive/guitar-pedal-app/build/index.html");
    if (file.existsAsFile()) {
        webView->goToURL("file://" + file.getFullPathName());
    } else {
        DBG("Arquivo não encontrado: " + file.getFullPathName());
    }
}

void CueioDriveAudioProcessorEditor::paint(juce::Graphics& g) {
    g.fillAll(juce::Colours::black); // Pintando a interface
}

void CueioDriveAudioProcessorEditor::resized() {
    webView->setBounds(getLocalBounds()); // Redimensionando o WebView
}
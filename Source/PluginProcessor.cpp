#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <JucePluginDefines.h>

//==============================================================================
CueioDriveAudioProcessor::CueioDriveAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
    parameters(*this, nullptr, juce::Identifier("CueioDrive"),
               {
                   std::make_unique<juce::AudioParameterFloat>("drive", "Drive", 1.f, 25.f, 1.f),
                   std::make_unique<juce::AudioParameterFloat>("range", "Range", 0.f, 3000.f, 1000.f),
                   std::make_unique<juce::AudioParameterFloat>("blend", "Blend", 0.f, 1.f, 1.f),
                   std::make_unique<juce::AudioParameterFloat>("volume", "Volume", 0.f, 1.f, 0.5f)
               })
#endif
{
}

CueioDriveAudioProcessor::~CueioDriveAudioProcessor()
{
}

//==============================================================================
const juce::String CueioDriveAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool CueioDriveAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool CueioDriveAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool CueioDriveAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double CueioDriveAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int CueioDriveAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int CueioDriveAudioProcessor::getCurrentProgram()
{
    return 0;
}

void CueioDriveAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String CueioDriveAudioProcessor::getProgramName (int index)
{
    return {};
}

void CueioDriveAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void CueioDriveAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void CueioDriveAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool CueioDriveAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void CueioDriveAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // Limpar os canais de saída que não estão sendo usados
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // Pegando os valores atualizados do frontend
    auto* driveParam = parameters.getRawParameterValue("drive");
    auto* rangeParam = parameters.getRawParameterValue("range");
    auto* blendParam = parameters.getRawParameterValue("blend");
    auto* volumeParam = parameters.getRawParameterValue("volume");

    float drive = driveParam->load();    // Valor atualizado do frontend
    float range = rangeParam->load();    // Valor atualizado do frontend
    float blend = blendParam->load();    // Valor atualizado do frontend
    float volume = volumeParam->load();  // Valor atualizado do frontend

    // Processamento dos sinais, como antes
    if (totalNumInputChannels == 1 && totalNumOutputChannels == 2)
    {
        auto* monoData = buffer.getWritePointer(0);
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            float cleanSig = monoData[sample];
            float driveSig = std::tanh(drive * cleanSig);

            driveSig *= range;
            driveSig = std::tanh(driveSig / 1000) * 1000;
            driveSig /= range;

            float outSig = (1 - blend) * cleanSig + blend * driveSig;
            monoData[sample] = outSig * volume;
        }

        // Copiar os dados do canal esquerdo (0) para o canal direito (1)
        buffer.copyFrom(1, 0, buffer, 0, 0, buffer.getNumSamples());
    }
    else
    {
        for (int channel = 0; channel < totalNumInputChannels; ++channel)
        {
            auto* channelData = buffer.getWritePointer(channel);

            for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
            {
                float cleanSig = channelData[sample];
                float driveSig = std::tanh(drive * cleanSig);

                driveSig *= range;
                driveSig = std::tanh(driveSig / 1000) * 1000;
                driveSig /= range;

                float outSig = (1 - blend) * cleanSig + blend * driveSig;
                channelData[sample] = outSig * volume;
            }
        }
    }
}



//==============================================================================
bool CueioDriveAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* CueioDriveAudioProcessor::createEditor()
{
    return new CueioDriveAudioProcessorEditor (*this);
}

//==============================================================================
void CueioDriveAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void CueioDriveAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new CueioDriveAudioProcessor();
}

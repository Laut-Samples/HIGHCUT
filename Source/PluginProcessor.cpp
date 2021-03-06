/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
LAUTEQHIGHCUTAudioProcessor::LAUTEQHIGHCUTAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

LAUTEQHIGHCUTAudioProcessor::~LAUTEQHIGHCUTAudioProcessor()
{
}

//==============================================================================
const juce::String LAUTEQHIGHCUTAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool LAUTEQHIGHCUTAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool LAUTEQHIGHCUTAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool LAUTEQHIGHCUTAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double LAUTEQHIGHCUTAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int LAUTEQHIGHCUTAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int LAUTEQHIGHCUTAudioProcessor::getCurrentProgram()
{
    return 0;
}

void LAUTEQHIGHCUTAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String LAUTEQHIGHCUTAudioProcessor::getProgramName (int index)
{
    return {};
}

void LAUTEQHIGHCUTAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void LAUTEQHIGHCUTAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    juce::dsp::ProcessSpec spec;
    
    spec.maximumBlockSize = samplesPerBlock;
    
    spec.numChannels = 1;
    
    spec.sampleRate = sampleRate;
    
    leftChain.prepare(spec);
    rightChain.prepare(spec);
    

    updateFilters();
    
}

void LAUTEQHIGHCUTAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool LAUTEQHIGHCUTAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void LAUTEQHIGHCUTAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    
    
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());


    updateFilters();
    
    
    juce::dsp::AudioBlock<float> block(buffer);
    
    auto leftBlock = block.getSingleChannelBlock(0);
    auto rightBlock = block.getSingleChannelBlock(1);
    
    juce::dsp::ProcessContextReplacing<float> leftContext(leftBlock);
    juce::dsp::ProcessContextReplacing<float> rightContext(rightBlock);
    
    leftChain.process(leftContext);
    rightChain.process(rightContext);
    
    
    
}

//==============================================================================
bool LAUTEQHIGHCUTAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* LAUTEQHIGHCUTAudioProcessor::createEditor()

{
        return new LAUTEQHIGHCUTAudioProcessorEditor (*this);
//    return new juce::GenericAudioProcessorEditor(*this);
}

//==============================================================================
void LAUTEQHIGHCUTAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    
    // PARAMETER SPEICHERN
    juce::MemoryOutputStream mos(destData, true);
    apvts.state.writeToStream(mos);
}

void LAUTEQHIGHCUTAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    
        // PARAMETER SPEICHERN
    
    auto tree = juce::ValueTree::readFromData(data, sizeInBytes);
    if( tree.isValid() )
    {
        apvts.replaceState(tree);
        updateFilters();
    }
    
    
    // Chain Settings
}

ChainSettings getChainSettings(juce::AudioProcessorValueTreeState& apvts)
{
    ChainSettings settings;
    
    settings.lowCutFreq = apvts.getRawParameterValue("LowCut Freq")->load();
    settings.highCutFreq = apvts.getRawParameterValue("HighCut Freq")->load();
    settings.peakFreq = apvts.getRawParameterValue("Peak Freq")->load();
    settings.peakGainInDecibels = apvts.getRawParameterValue("Peak Gain")->load();
    settings.peakQuality = apvts.getRawParameterValue("Peak Quality")->load();
    settings.lowCutSlope = static_cast<Slope>(apvts.getRawParameterValue("LowCut Slope")->load());
    settings.highCutSlope = static_cast<Slope>(apvts.getRawParameterValue("HighCut Slope")->load());
    
    settings.filtershapes = apvts.getRawParameterValue("FILTERTYPES");
    
    getFilterTypes().setFilterType (filterarten)
    
    return settings;
}



// PEAK

void LAUTEQHIGHCUTAudioProcessor::updatePeakFilter(const ChainSettings &chainSettings)
{
    auto peakCoefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(getSampleRate(),
                                                                                chainSettings.peakFreq,
                                                                                chainSettings.peakQuality,
                                                                                juce::Decibels::decibelsToGain(chainSettings.peakGainInDecibels));
    
    updateCoefficients(leftChain.template get<ChainPositions::Peak>().coefficients, peakCoefficients);
    updateCoefficients(rightChain.template get<ChainPositions::Peak>().coefficients, peakCoefficients);
}

void LAUTEQHIGHCUTAudioProcessor::updateCoefficients(Coefficients& old, const Coefficients& replacements)
    {
        *old = *replacements;
    }

//LOWCUT

void LAUTEQHIGHCUTAudioProcessor::updateLowCutFilters(const ChainSettings &chainSettings)
{
    auto cutCoefficients = juce::dsp::FilterDesign<float>::designIIRHighpassHighOrderButterworthMethod(chainSettings.lowCutFreq, getSampleRate(), 2 * (chainSettings.lowCutSlope +1));
    
    auto& leftLowCut = leftChain.get<ChainPositions::LowCut>();
    auto& rightLowCut = rightChain.get<ChainPositions::LowCut>();
    
    updateCutFilter(leftLowCut, cutCoefficients, chainSettings. lowCutSlope);
    updateCutFilter(rightLowCut, cutCoefficients, chainSettings.lowCutSlope);

    
}


// HIGHCUT

    void LAUTEQHIGHCUTAudioProcessor::updateHighCutFilters(const ChainSettings &chainSettings)
{
    
    auto highCutCoefficients = juce::dsp::FilterDesign<float>::designIIRLowpassHighOrderButterworthMethod(chainSettings.highCutFreq,
                                                                                                          getSampleRate(),
                                                                                                          2 * (chainSettings.highCutSlope +1));
    
    auto& leftHighCut = leftChain.get<ChainPositions::HighCut>();
    auto& rightHighCut = rightChain.get<ChainPositions::HighCut>();
    
    updateCutFilter(leftHighCut, highCutCoefficients, chainSettings.highCutSlope);
    updateCutFilter(rightHighCut, highCutCoefficients, chainSettings.highCutSlope);
    
}


// Update Filters

void LAUTEQHIGHCUTAudioProcessor::updateFilters()
{
    auto chainSettings = getChainSettings(apvts);
    
    // Peak
    updatePeakFilter(chainSettings);
    
    // Filter
    updateLowCutFilters(chainSettings);
    updateHighCutFilters(chainSettings);
}


// Parameter

    juce::AudioProcessorValueTreeState::ParameterLayout LAUTEQHIGHCUTAudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    
    // LOW CUT
    
    layout.add(std::make_unique<juce::AudioParameterFloat>("LowCut Freq",
                                                           "LowCut Freq",
                                                           juce::NormalisableRange<float>(20.f,20000.f, 1.f, 0.25f),
                                                           20.f));
    
    // HIGH CUT
    
    layout.add(std::make_unique<juce::AudioParameterFloat>("HighCut Freq",
                                                           "HighCut Freq",
                                                           juce::NormalisableRange<float>(20.f,20000.f, 1.f, 0.25f),
                                                           20000.f));  
    
    // PEAK 1 VON 4
    
    layout.add(std::make_unique<juce::AudioParameterFloat>("Peak Freq",
                                                           "Peak Freq",
                                                           juce::NormalisableRange<float>(20.f,20000.f, 1.f, 0.25f),
                                                           750.f));
    
    layout.add(std::make_unique<juce::AudioParameterFloat>("Peak Gain",
                                                           "Peak Gain",
                                                           juce::NormalisableRange<float>(-24.f, 24.f, 0.5f, 1.f),
                                                           0.0f));
    
    layout.add(std::make_unique<juce::AudioParameterFloat>("Peak Quality",
                                                           "Peak Quality",
                                                           juce::NormalisableRange<float>(0.1f, 10.f, 0.05f, 1.f),
                                                           1.f));
    
    
    
    // FilterTypes ARRAY
//    
    juce::StringArray Array;
    for( int i = 0; i < 4; ++i )
    {
        juce::String str;
        str << (12 + i*12);
        str << "db/Oct";
        Array.add(str);
    
    }
    
    layout.add(std::make_unique<juce::AudioParameterChoice>("LowCut Freq", "lowCut Freq", Array, 0 ));
    layout.add(std::make_unique<juce::AudioParameterChoice>("HighCut Freq", "highCut Freq", Array, 0 ));
    
    // FILTERTYPES COMBOBOX
    
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    std::make_unique<juce::AudioParameterChoice>("FILTERTYPES",
                                                 "fitlertypes",
                                                 juce::StringArray
                                                            {       "HighCut 1",
                                                                    "HighCut 2",
                                                                    "LowCut 1",
                                                                    "LowCut 2", },
                                                                    0);
    
    
//    juce::AudioParameterChoice("Filter Slope",
//                                                 "filter slope",
//                                                 juce::StringArray {"HighCut","LowCut","Peak",}, 0);

    
    


    
    
    return layout;
    

}


//    juce::AudioProcessorValueTreeState::ComboBoxAttachment LAUTEQHIGHCUTAudioProcessor::createParameter()
//
//{
//
//}
//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new LAUTEQHIGHCUTAudioProcessor();
}

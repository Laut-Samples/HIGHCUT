/*
  ==============================================================================

    FilterData.cpp
    Created: 16 Jan 2022 10:46:46pm
    Author:  Kai

  ==============================================================================
*/
#include <JuceHeader.h>
#include "FilterData.h"


void FilterData::prepareToPlay (double sampleRate, int samplesPerBlock, int numChannels)
{
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = numChannels;

    filter.prepare (spec);
    
    
}
void FilterData::process (juce::AudioBuffer<float>& buffer)
{
    juce::dsp::AudioBlock<float> block { buffer };
    
    filter.process (juce::dsp::ProcessContextReplacing<float> { block });
    
}

void FilterData::updateParameters(const int filterType, const float frequency, const float resonace)

{
    switch (filterType)
    {
        case 0:
            // High Cut 12 db/Oct
            filter.coefficients (juce::dsp::FilterDesign<float>::designIIRLowpassHighOrderButterworthMethod(getChainSettings, getsampleRate(), 2)
            
            break;
            
        case 1:
            // High Cut 24 db/Oct
            filter.coefficients (juce::dsp::FilterDesign<float>::designIIRLowpassHighOrderButterworthMethod(getChainSettings, getsampleRate(), 4)
            
            break;
            
        case 2:
            // Low Cut 12 db/Oct
            filter.coefficients (juce::dsp::FilterDesign<float>::designIIRHighpassHighOrderButterworthMethod(getChainSettings, getsampleRate(), 2)
            
            break;
            
        case 3:
            // High Cut 24 db/Oct
            filter.coefficients (juce::dsp::FilterDesign<float>::designIIRHighpassHighOrderButterworthMethod(getChainSettings, getsampleRate(), 4)
            break;
            
        default:
            jassertfalse;
            break;
    }
        
};



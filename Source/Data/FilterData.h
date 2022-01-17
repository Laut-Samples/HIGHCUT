/*
  ==============================================================================

    FilterData.h
    Created: 16 Jan 2022 10:46:46pm
    Author:  Kai

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "ChainSettings.h"



class FilterData
{
public:
    
    void prepareToPlay (double sampleRate, int samplesPerBlock, int numChannels);
    void process (juce::AudioBuffer<float>& buffer);
    void updateParameters(const int filterType, const float frequency, const float resonace);
    void reset();
    
    void setFilterTypes(const int choice);

private:

    //Slider
//    CustomRotarySlider highCutFreqSlider, highCutSlope, lowCutFreqSlider;
    
    
//    juce::dsp::IIRLowpassHighOrderButterworthMethod<float> filter;
    juce::dsp::IIR::Filter<float> filter;
};

/*
  ==============================================================================

    ChainSettings.h
    Created: 17 Jan 2022 2:19:19am
    Author:  Kai

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

enum Slope
{
    Slope_12,
    Slope_24,
    Slope_36,
    Slope_48
    
};

struct ChainSettings
{
    float peakFreq { 0 }, peakGainInDecibels{0}, peakQuality {1.f};
    float lowCutFreq { 0 }, highCutFreq { 0 };
    
    Slope lowCutSlope {Slope::Slope_12}, highCutSlope {Slope::Slope_12};
};


ChainSettings getChainSettings(juce::AudioProcessorValueTreeState& apvts);


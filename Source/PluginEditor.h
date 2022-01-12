/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

struct CustomRotarySlider : juce::Slider
{
    CustomRotarySlider() : juce::Slider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag,
                                        juce::Slider::TextEntryBoxPosition::NoTextBox)
    {
        
    }
};

//==============================================================================
/**
*/
class LAUTEQHIGHCUTAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    LAUTEQHIGHCUTAudioProcessorEditor (LAUTEQHIGHCUTAudioProcessor&);
    ~LAUTEQHIGHCUTAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    LAUTEQHIGHCUTAudioProcessor& audioProcessor;
    
    // Image
    juce::ImageComponent mImageComponent;
    
    //Slider
    CustomRotarySlider highCutFreqSlider;
    
    std::vector<juce::Component*>getComps();
    
    using APVTS = juce::AudioProcessorValueTreeState;
    using Attachment = APVTS::SliderAttachment;
    
    Attachment highCutFreqSliderAttachment;
    
//    juce::ImageComponent oImageComponent;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LAUTEQHIGHCUTAudioProcessorEditor)
};

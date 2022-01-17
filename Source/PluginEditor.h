/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

struct LookAndFeel : juce::LookAndFeel_V4
{
    void drawToggleButton (juce::Graphics &g,
                           juce::ToggleButton & toggleButton);
    
    
};
//==============================================================================
struct ComboBox : juce::ComboBox
{
    
};

//  ==============================================================================
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
//    Placeholder controlBar;
//    GlobalControls globalControls;
    
    LAUTEQHIGHCUTAudioProcessor& audioProcessor;
    
    // Image
    juce::ImageComponent mImageComponent;
    
    // ComboBox
    ComboBox FilterTypes;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> FilterTypesAttachment;

    
    ChainSettings getChainSettings(juce::AudioProcessorValueTreeState& apvts);
    
    std::vector<juce::Component*>getComps();
    using APVTS = juce::AudioProcessorValueTreeState;
    
    
    // ComboBox
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    Attachment highCutFreqSliderAttachment;
    Attachment highCutSlopeAttachment;
    Attachment lowCutFreqSliderAttachment;
    
    
    
    
   
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LAUTEQHIGHCUTAudioProcessorEditor)
};

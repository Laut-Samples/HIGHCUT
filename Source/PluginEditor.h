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
    
//    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> highCutSlope;
    
    

    
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
//    Placeholder controlBar;
//    GlobalControls globalControls;
    
    LAUTEQHIGHCUTAudioProcessor& audioProcessor;
    
    // Image
    juce::ImageComponent mImageComponent;
    
    //Slider
    CustomRotarySlider highCutFreqSlider, highCutSlope;
    
    ComboBox FilterTypes;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> FilterTypesAttachment;
    
    std::vector<juce::Component*>getComps();
    
    using APVTS = juce::AudioProcessorValueTreeState;
   
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
//    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> highCutSlopeAttachment;
    
    Attachment highCutFreqSliderAttachment;
    Attachment highCutSlopeAttachment;
    
    
//    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> highCutSlope;
    
    
//    juce::ComboBoxParameterAttachment
    
    
    
    
   
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LAUTEQHIGHCUTAudioProcessorEditor)
};

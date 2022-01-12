/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LAUTEQHIGHCUTAudioProcessorEditor::LAUTEQHIGHCUTAudioProcessorEditor (LAUTEQHIGHCUTAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),

highCutFreqSliderAttachment(audioProcessor.apvts, "HighCut Freq", highCutFreqSlider)

{
    
    //IMAGE
    
    auto tapImage = juce::ImageCache::getFromMemory(BinaryData::Knob1_png, BinaryData::Knob1_pngSize);
    
    
    if(! tapImage.isNull())
        mImageComponent.setImage (tapImage, juce::RectanglePlacement::stretchToFit);
    else
        jassert (! tapImage.isNull());
    
    addAndMakeVisible(mImageComponent);
    
    // SLIDER
    
    for( auto* comp : getComps() )
    {
        addAndMakeVisible (comp);
        
    }
    
    
//    
    
//     Make sure that before the constructor has finished, you've set the
//     editor's size to whatever you need it to be.
    setSize (500, 400);
}

LAUTEQHIGHCUTAudioProcessorEditor::~LAUTEQHIGHCUTAudioProcessorEditor()
{
}

//==============================================================================
void LAUTEQHIGHCUTAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
//    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

//    g.setColour (juce::Colours::white);
//    g.setFont (15.0f);
//    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
    
}

void LAUTEQHIGHCUTAudioProcessorEditor::resized()
{
    
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    mImageComponent.setBoundsRelative(0.0f, 0.0f, 1.0f, 1.0f);
    
    
    highCutFreqSlider.setBoundsRelative(0.25f, 0.25f, 0.29f, 0.5f);
    highCutFreqSlider.setCentrePosition(250, 200);
    
    
}

    
    std::vector<juce::Component*>LAUTEQHIGHCUTAudioProcessorEditor::getComps()
{
    return
    {
        &highCutFreqSlider,
    };
    
}

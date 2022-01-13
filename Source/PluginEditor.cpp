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

highCutFreqSliderAttachment(audioProcessor.apvts, "HighCut Freq", highCutFreqSlider),
highCutSlopeAttachment(audioProcessor.apvts, "HighCut Slope", highCutSlope)
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
    

    
//    addAndMakeVisible(controlBar);
    
    
    
    // COMBOBOX FilterTypes
    
    addAndMakeVisible(highCutSlope);

    addAndMakeVisible(FilterTypes);
    FilterTypes.setName("FILTERTYPES");
    
    FilterTypes.addItem ("12 db/Oct",  1);
    FilterTypes.addItem ("24 db/Oct",  2);
    FilterTypes.addItem ("36 db/Oct", 3);
    FilterTypes.addItem ("48 db/Oct", 4);
    FilterTypes.setSelectedId(1);
    
    comboBox:   
//    FilterTypes = new juce::AudioProcessorValueTreeState::ComboBoxAttachment
    
//    FilterTypes.addListener(highCutSlope);
    
//    FilterTypes = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "HighCut Slope", FilterTypes )
//    styleMenu.onChange = [this] { styleMenuChanged(); };
//    styleMenu.setSelectedId (1);
    
    
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
    
    //Image
    mImageComponent.setBoundsRelative(0.0f, 0.0f, 1.0f, 1.0f);
    
    // HighCut
    highCutFreqSlider.setBoundsRelative(0.25f, 0.25f, 0.29f, 0.5f);
    highCutFreqSlider.setCentrePosition(250, 200);
    
    auto bounds = getLocalBounds();
    
//    highCutSlope.setBoundsRelative(0.25f, 0.25f, 0.29f, 0.5f);
//    highCutSlope.setCentrePosition(200, 200);
    
    /// ComboBOX FilterTypes
    
    FilterTypes.setBounds( bounds.removeFromBottom(125) );
    FilterTypes.setBoundsRelative(0.05f, 0.2f, 0.2f, 0.05f);
    FilterTypes.setCentrePosition(250, 290);
    
//    highCutSlope.setBounds( bounds.removeFromBottom(125) );
//    highCutSlope.setBoundsRelative(0.05f, 0.2f, 0.2f, 0.05f);
//    highCutSlope.setCentrePosition(250, 290);
    
//    void LAUTEQHIGHCUTAudioProcessorEditor::comboBoxedChanged(comboBox* box)
//    {
//
//    }

    
//    highCutSlope.
    
}

    
    std::vector<juce::Component*>LAUTEQHIGHCUTAudioProcessorEditor::getComps()
{
    return
    {
        &highCutFreqSlider,
        &highCutSlope,
    };
    
}

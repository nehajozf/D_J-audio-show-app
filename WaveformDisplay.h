/*
  ==============================================================================

    WaveformDisplay.h
    Created: 11 Feb 2023 3:00:33pm
    Author:  Neha Joseph

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class WaveformDisplay  : public juce::Component,
                         public juce::ChangeListener
{
public:
    WaveformDisplay(juce::AudioFormatManager & formatManagerToUse,
                    juce::AudioThumbnailCache & cacheToUse);
    ~WaveformDisplay() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void changeListenerCallback(juce::ChangeBroadcaster *source) override;
    
    void loadURL(juce::URL audioURL);
    
    /** Set the relative position of the playhead*/
    void setPositionRelative(double pos);

private:
    
    juce::AudioThumbnail audioThumb;
    
    bool fileLoaded;
    
    double position;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};

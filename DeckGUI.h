/*
  ==============================================================================

    DeckGUI.h
    Created: 10 Feb 2023 5:54:26am
    Author:  Neha Joseph

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "DJAudioPlayer.h"

#include "WaveformDisplay.h"

#include "PlaylistComponent.h"

//==============================================================================
/*
*/
class DeckGUI  : public juce::Component,
                 public juce::Button::Listener,
                 public juce::Slider::Listener,
                 public juce::FileDragAndDropTarget,
                 public juce::Timer
{
public:
    DeckGUI(DJAudioPlayer* player,
            juce::AudioFormatManager & formatManagerToUse,
            juce::AudioThumbnailCache & cacheToUse);
    ~DeckGUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    
    /** Implement Button::Listner */
    void buttonClicked (juce::Button *) override;
    
    /** Implement Slider::Listner */
    void sliderValueChanged (juce::Slider *) override;
    
    
    
    bool isInterestedInFileDrag(const juce::StringArray &files) override;
    
    void filesDropped(const juce::StringArray &files, int x, int y) override;
    
    void timerCallback() override;
    
    
    
    void playlistToDeckGUI();
    
    
    

private:
    
    juce::TextButton playButton{"PLAY"};
    
    juce::TextButton stopButton{"STOP"};
    
    juce::TextButton loadButton{"LOAD"};
    
    
    juce::ToggleButton loopButton{ "LOOP" };
    
    juce::TextEditor trackName;
    
    juce::String mtrackName;
    
    
    juce::Slider volSlider;
    
    juce::Slider speedSlider;
    
    juce::Slider posSlider;
    
    DJAudioPlayer* player;
    
   // juce::FileChooser fChooser{"Select a file..."};
   // void loadURL(juce::URL audioURL);

    
    WaveformDisplay waveformDisplay;
    
    
    juce::Label volSliderLabel;
    
    juce::Label speedSliderLabel;
    
    juce::Label posSliderLabel;
    
    
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};

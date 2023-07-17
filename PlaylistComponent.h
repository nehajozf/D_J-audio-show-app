/*
  ==============================================================================

    PlaylistComponent.h
    Created: 13 Feb 2023 5:44:44am
    Author:  Neha Joseph

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include <vector>

#include <string>

#include <iostream>
#include <fstream>
#include <ostream>


//other people new code

#include "DeckGUI.h"
#include "WaveformDisplay.h"
#include <fstream>

//other people till here


//==============================================================================


class PlaylistComponent  : public juce::Component,
                           public juce::TableListBoxModel,
                           public juce::Button::Listener
                           
         
{
public:
    
    PlaylistComponent();
    
    
    
    ~PlaylistComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    
    int getNumRows() override;
    
    void paintRowBackground(juce::Graphics &,
                            int rowNumber,
                            int width,
                            int height,
                            bool rowIsSelected) override;
    
    void paintCell(juce::Graphics &,
                   int rowNumber,
                   int columnId,
                   int width,
                   int height,
                   bool rowIsSelected) override;
    
    Component* refreshComponentForCell(int rowNumber,
                                       int columnId,
                                       bool isRowSelected,
                                       Component *existingComponentToUpdate) override;
    
    void buttonClicked(juce::Button* button) override;
    
    
    
    
  
    
    
    
    void textEditorTextChanged(juce::TextEditor& editor);
    
    void deleteFile();
    
    void loadFileIntoDeck1();
    
    void loadFileIntoDeck2();
    
    juce::String fileToDeckGUI;
    
    std::string stdstring;
    
    


private:
    
   // juce::TableListBox tableComponent;
    
    
    
    
    std::vector<std::string> trackTitles;
    
   
    juce::TextButton loadPlaylistButton{ "Load Playlist" };
    
    void loadPlaylist();
    
    
    
    juce::AudioFormatManager formatManager;
    
    juce::Array<juce::File> myFiles;
    
    std::vector<std::string> existingFiles;
    
    double duration;
    
    juce::String fileName;
    
    juce::Array<double> myFilesDuration;
    
    juce::Array<juce::String> fileNames;
    
    juce::TableListBox tableComponent;
    
    juce::TextButton libraryLoadButton{"Load into library"};
    
    bool historyClicked = false;
    
    int duplicateIndex = -1;
    
    juce::TextButton libraryDeleteButton;
    
    juce::TextButton libraryDeck1;
    
    juce::TextButton libraryDeck2;
    
    juce::TextEditor librarySearch{ "Search for tracks..." };
    
    juce::String searchInput;
        
    double rowclicked;
    
    double columnclicked;

    
    
    DJAudioPlayer* player;
    
   
   
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};

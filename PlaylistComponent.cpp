/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 13 Feb 2023 5:44:44am
    Author:  Neha Joseph

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"

#include <string>



//==============================================================================

PlaylistComponent::PlaylistComponent()




{





    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
   
    
    
    
    tableComponent.getHeader().addColumn("Track Name", 1, 300);
    
    tableComponent.getHeader().addColumn("Time", 2, 100);
    
    tableComponent.getHeader().addColumn("Load to Deck 1(Left)", 3, 150);
    
    tableComponent.getHeader().addColumn("Load to Deck 2(Right)", 4, 150);
    
    tableComponent.getHeader().addColumn("Delete", 5, 100);
    
  
    
    
    tableComponent.setModel(this);
    
    addAndMakeVisible(tableComponent);
    
   
    
    addAndMakeVisible(libraryLoadButton);
    
    addAndMakeVisible(librarySearch);
    
    libraryLoadButton.addListener(this);
    
    formatManager.registerBasicFormats();
       
    
    
    //code for loading to playlist to deck 1 or deck 2
    std::ofstream myfile("playlist.txt");
    
    myfile << stdstring << std::endl << "0" << std::endl;
    
    myfile.close();

    
    std::ifstream file("PlaylistHistory.txt");
    
    std::string str;
    
    std::vector<std::string> lines;
    
    while (std::getline(file, str))
    {
        
        lines.push_back(str);
    }

    
    for (int i = 0; i < lines.size(); ++i)
    {
        
        existingFiles.push_back(lines[i]);
    }

    
    if (existingFiles.size() != 0) {

       
        for (int i = 0; i < existingFiles.size(); ++i) {
            
            myFiles.add(juce::File{ existingFiles[i] });

        }

        for (int i = 0; i < myFiles.size(); ++i) {

            fileName = juce::URL::removeEscapeChars(juce::URL{ myFiles[i] }.getFileName());
            
            fileNames.add(fileName);
            
            juce::AudioFormatReader* reader = formatManager.createReaderFor(myFiles[i]);
            
            duration = reader->lengthInSamples / reader->sampleRate;
            
            myFilesDuration.add(duration);

        }
        tableComponent.updateContent();
    }
    
    
    
   
  
    
 
  
    
    

}

    PlaylistComponent::~PlaylistComponent()
{
    
}

void PlaylistComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("PlaylistComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
    
    
}

void PlaylistComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    
  
    
   
    
    double rowH = getHeight() / 8;
    
        libraryLoadButton.setBounds(0, 0, getWidth() / 2, rowH);
    
        librarySearch.setBounds(getWidth() / 2, 0, getWidth() / 2, rowH);
    
        tableComponent.setBounds(0, rowH, getWidth(), getHeight());

        
        tableComponent.getHeader().setColumnWidth(1, (getWidth() / 8) * 3);
    
        tableComponent.getHeader().setColumnWidth(2, getWidth() / 7);
    
        tableComponent.getHeader().setColumnWidth(3, (getWidth() / 8) * 1.5);
    
        tableComponent.getHeader().setColumnWidth(4, (getWidth() / 8) * 1.5);
    
        tableComponent.getHeader().setColumnWidth(5, (getWidth() / 9));

        
        tableComponent.setColour(juce::ListBox::backgroundColourId, juce::Colours::cornflowerblue);
        
        
        librarySearch.setTextToShowWhenEmpty("Search for tracks here..", juce::Colours::orchid);
    
        librarySearch.setFont(20.0f);

    
  
   
    
    
    
    
}


int PlaylistComponent::getNumRows()
{
    
    
   // return trackTitles.size();
    
    
    
    return fileNames.size();
    
   
 
    
    
    
    
}

void PlaylistComponent::paintRowBackground(juce::Graphics & g,
                        int rowNumber,
                        int width,
                        int height,
                        bool rowIsSelected)
{
    
    if(rowIsSelected)
    {
       // g.fillAll(juce::Colours::orange);
        g.fillAll(juce::Colour::fromRGB(174,100,150));
    }
    else
    {
       // g.fillAll(juce::Colours::darkgrey);
        g.fillAll(juce::Colour::fromRGB(193, 150, 250));
    }
    
}

void PlaylistComponent::paintCell(juce::Graphics & g,
               int rowNumber,
               int columnId,
               int width,
               int height,
               bool rowIsSelected)
{
    
   
    
   
    
    
    // Name of track song name in column 1
    if (columnId == 1) {
        
                g.drawText(fileNames[rowNumber],
                    2, 0,
                    width - 4, height,
                    juce::Justification::centredLeft,
                    true);
            }
    
    //Duration of the track song in column 2
            if (columnId == 2) {
                
                std::time_t seconds(myFilesDuration[rowNumber]);
                tm* p = gmtime(&seconds);
                std::string hhmmss;
                std::string hours;
                std::string mins;
                std::string secs;
                
                //Convert time or duration to minutes and seconds
                if (p->tm_hour < 10) {
                    
                    hours = "0" + std::to_string(p->tm_hour);
                }
                
                else {
                    
                    hours = std::to_string(p->tm_hour);
                }
                
                if (p->tm_min < 10) {
                    
                    mins = "0" + std::to_string(p->tm_min);
                }
                
                else {
                    
                    mins = std::to_string(p->tm_min);
                }
                
                if (p->tm_sec < 10) {
                    
                    secs = "0" + std::to_string(p->tm_sec);
                }
                
                else {
                    
                    secs = std::to_string(p->tm_sec);
                }

                hhmmss = hours + ":" + mins + ":" + secs;
                g.drawText(hhmmss,
                    2, 0,
                    width - 4, height,
                    juce::Justification::centredLeft,
                    true);
            }

    
   

    
 
}


juce::Component* PlaylistComponent::refreshComponentForCell(int rowNumber,
                                   int columnId,
                                   bool isRowSelected,
                                   Component *existingComponentToUpdate)
{
   

    
  
    
    if (columnId == 3) {
        
            if (existingComponentToUpdate == nullptr) {
                
                juce::TextButton* btn = new juce::TextButton{ "Deck 1" };
                
                juce::String id{ std::to_string(rowNumber) };
                
                btn->setComponentID(id);
                
                btn->addListener(this);
                
                existingComponentToUpdate = btn;
                
                btn->onClick = [this] {loadFileIntoDeck1(); };
            }
        }
    
    
 
    
    
    
    if (columnId == 4) {
        
           if (existingComponentToUpdate == nullptr) {
               
               juce::TextButton* btn = new juce::TextButton{ "Deck 2" };
               
               juce::String id{ std::to_string(rowNumber) };
               
               btn->setComponentID(id);
               
               btn->addListener(this);
               
               existingComponentToUpdate = btn;
               
               btn->onClick = [this] {loadFileIntoDeck2(); };
           }
       }
    
   
   
    
   
    
    if (columnId == 5) {
        
            if (existingComponentToUpdate == nullptr) {
                
                juce::TextButton* btn = new juce::TextButton{ "Delete" };
                
                juce::String id{ std::to_string(rowNumber) };
                
                btn->setComponentID(id);
                
                btn->addListener(this);
                
                existingComponentToUpdate = btn;
                
                btn->onClick = [this] {deleteFile(); };
                        

            }
        }
    
  
    
    return existingComponentToUpdate;

}






void PlaylistComponent::buttonClicked(juce::Button* button)
{
    
    //my code
    
    //    int id = std::stoi(button->getComponentID().toStdString());
    
    // std::cout<<"PlaylistComponent::buttonClicked " << button->getComponentID() << std::endl;
    
    //    std::cout<<"PlaylistComponent::buttonClicked " << trackTitles[id] << std::endl;
    
    
   
    
    //When the load button is clicked, it goes into library
    if (button == &libraryLoadButton) {
        
        //helps to choose multiple files at once
        juce::FileChooser choosers{ "Select for file(s) to add to the library...", juce::File() , "*.mp3;*.wav;*.aiff" };
        
        
        
        
        if (choosers.browseForMultipleFilesToOpen()) {
            
            
            //chooses myFiles
            myFiles = choosers.getResults();
            
            //Repeats the size of myFiles
            for (int i = 0; i < myFiles.size(); ++i) {
                
                //to check if file exists
                if (existingFiles.size() != 0 || i == 0) {
                    
                    //loops through the file
                    for (int j = 0; j < existingFiles.size(); ++j) {
                        
                        //loops through the existing file
                        if (myFiles[i].getFullPathName().toStdString() == existingFiles[j]) {
                            
                            DBG("There are duplicates");
                            
                            
                            //creates an alert window
                            juce::AlertWindow alertDuplicate("Duplicate file added", "Duplicated file " + juce::URL::removeEscapeChars(juce::URL{ myFiles[i] }.getFileName()) + " has not been added", juce::MessageBoxIconType::InfoIcon);
                            
                            alertDuplicate.addButton("Continue",0);
                            
                            alertDuplicate.setUsingNativeTitleBar(true);
                            
                              
                            
                            //to check if index id duplicated
                            duplicateIndex = i;
                            
                            break;
                        }
                        
                        
                    }
                    
                    //to check if index is not duplicated
                    if (i != duplicateIndex) {
                        
                        //to display the file name
                        fileName = juce::URL::removeEscapeChars(juce::URL{ myFiles[i] }.getFileName());
                        
                        fileNames.add(fileName);
                        
                        juce::AudioFormatReader* reader = formatManager.createReaderFor(myFiles[i]);
                        
                        //gets duration of track song
                        duration = reader->lengthInSamples / reader->sampleRate;
                        
                        myFilesDuration.add(duration);
                        
                        DBG(fileNames[i]);
                        
                        DBG(duration);
                        
                        // path is added to  existing array
                        existingFiles.push_back(myFiles[i].getFullPathName().toStdString());
                        
                    }
                    
                }
                
            }
            
            
            //opens text file
            std::ofstream history("PlaylistHistory.txt");
            
            for (int i = 0; i < existingFiles.size(); ++i) {
                
                history << existingFiles[i] << std::endl;
            }
            
            history.close();
            
            
            tableComponent.updateContent();
            
            
        }
        
    }
    
    
    //to check when row is clicked, should load them to deck 1 or deck 2 or delete the file
    rowclicked = button->getComponentID().getDoubleValue();
    
    columnclicked = button->getComponentID().getDoubleValue();
    
    

    
    
}
    
    





// Search option button
void PlaylistComponent::textEditorTextChanged(juce::TextEditor& editor) {
    
    //helps to type in the text
    searchInput = librarySearch.getText();
    
// Loops through the file
    for (int i = 0; i < fileNames.size(); ++i) {
        
        //Whatever word we type in, it helps to match it with the song name
        if (fileNames[i].containsWholeWord(searchInput) && searchInput != "") {
            
            //Helps to select the row which matches the name typed in the search option
            tableComponent.selectRow(i, false, true);
            
        }
    }
    
}

//For delete button
void PlaylistComponent::deleteFile() {
    
    DBG(rowclicked);

    for (int i = 0; i < myFiles.size(); ++i) {
        
        if (rowclicked == i) {
            
            
            juce::AlertWindow confirmDelete("Delete File", "Are you sure you want to delete this file?", juce::MessageBoxIconType::QuestionIcon);
            
            
            confirmDelete.setUsingNativeTitleBar(true);
            
            //Returns true when delete button is clicked
            confirmDelete.addButton("Delete", true);
            
            //If delete button is not clicked, returns false
            confirmDelete.addButton("Cancel", false);

            bool result = confirmDelete.isEnabled();

            if (result == true) {
                
                DBG("deletefile");
                
                fileNames.remove(i);
                
                myFilesDuration.remove(i);
                
                existingFiles.erase(existingFiles.begin() + i);
            }
            
            else{
                
                confirmDelete.exitModalState(true);
            }




        }
    }
    
    //Opens the PlaylistHistory text file, to remove the deleted file and update the current existing files
    std::ofstream history("PlaylistHistory.txt");
    for (int i = 0; i < existingFiles.size(); ++i) {
        history << existingFiles[i] << std::endl;
    }
    history.close();

    tableComponent.updateContent();
}

 // Loads song in Deck 1
void PlaylistComponent::loadFileIntoDeck1() {
    
    for (int i = 0; i < myFiles.size(); ++i) {
        
        //helps to create reader
        juce::AudioFormatReader* reader = formatManager.createReaderFor(myFiles[i]);
        
        if(columnclicked == 3){
            
            // Select which row we want to play in Deck 1
            if (rowclicked == i) {
                
                DBG("loadintodeck1");
                
                DBG(myFiles[i].getFileName());
                
                DBG(reader->getFormatName());
                
                fileToDeckGUI = myFiles[i].getFullPathName();
                
                //converts into std string
                stdstring = fileToDeckGUI.toStdString();
                
                //Replaces all \ in path to /, as reading the path into a file requires back slash"/"
                std::replace(stdstring.begin(), stdstring.end(), '\\', '/');
                
                DBG(stdstring);
                
                std::ofstream myfile("playlist.txt");
                
                //loads in deck 1
                myfile << stdstring << std::endl << "1" << std::endl;
                
                myfile.close();
                
              //  player->loadURL(juce::URL{ chooser.getResult() });
            }
        }
        
    }
    
    
}

//Load to Deck 2
void PlaylistComponent::loadFileIntoDeck2() {
    
    for (int i = 0; i < myFiles.size(); ++i) {
        
        juce::AudioFormatReader* reader = formatManager.createReaderFor(myFiles[i]);
        
        if (rowclicked == i) {
            
            DBG("loadintodeck2");
            
            DBG(myFiles[i].getFileName());
            
            DBG(reader->getFormatName());
            
            fileToDeckGUI = myFiles[i].getFullPathName();
            
            stdstring = fileToDeckGUI.toStdString();
            
            std::replace(stdstring.begin(), stdstring.end(), '\\', '/');
            
            DBG(stdstring);
            
            std::ofstream myfile("playlist.txt");
            
            myfile << stdstring << std::endl << "2" << std::endl;
            
            myfile.close();

            
        }
    }
}




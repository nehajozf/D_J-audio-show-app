/*
  ==============================================================================

    DeckGUI.cpp
    Created: 10 Feb 2023 5:54:26am
    Author:  Neha Joseph

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer* _player,
                 juce::AudioFormatManager & formatManagerToUse,
                 juce::AudioThumbnailCache & cacheToUse) : player(_player),
                                                           waveformDisplay(formatManagerToUse, cacheToUse)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
    
    addAndMakeVisible(playButton);
    
    addAndMakeVisible(stopButton);
    
    addAndMakeVisible(loadButton);
    
    addAndMakeVisible(waveformDisplay);
    
    
    
    addAndMakeVisible(trackName);
    
    addAndMakeVisible(loopButton);
    
    loopButton.addListener(this);
    
    
    
    
    addAndMakeVisible(volSlider);
    
    addAndMakeVisible(speedSlider);
    
    addAndMakeVisible(posSlider);
    
    
    
    
    
    
    volSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    
    speedSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    
    
    
    volSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 80, 25);
    
    speedSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 80, 25);
 
    
    
    posSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, true, 80, posSlider.getTextBoxHeight());
    
    
    //Text for volume slider
        volSliderLabel.setText("Volume", juce::NotificationType::dontSendNotification);
    
        volSliderLabel.attachToComponent(&volSlider, false);
    
    
    //Text for speed slider
        speedSliderLabel.setText("Speed", juce::NotificationType::dontSendNotification);
    
        speedSliderLabel.attachToComponent(&speedSlider, false);
    
    
        
    
    addAndMakeVisible (posSliderLabel);
    
    posSliderLabel.setText ("Position", juce::dontSendNotification);
    
    posSliderLabel.attachToComponent (&posSlider, true);
    
    
    
    
    
    //Adding colors to all buttons and the texts inside the button
    getLookAndFeel().setColour(juce::Slider::thumbColourId, juce::Colour::fromRGB(40,235,187));
    
    getLookAndFeel().setColour(juce::Slider::rotarySliderFillColourId, juce::Colour::fromRGB(200, 50, 80));
    
    getLookAndFeel().setColour(juce::Slider::trackColourId,juce::Colour::fromRGB(186, 42, 52));
    
    getLookAndFeel().setColour(juce::TextButton::buttonColourId, juce::Colour::fromRGB(220,20,60));
    
    getLookAndFeel().setColour(juce::TextButton::textColourOffId, juce::Colour::fromRGB(255,250,250));
    
    
    playButton.addListener(this);
    
    stopButton.addListener(this);
    
    loadButton.addListener(this);
    
    
    volSlider.addListener(this);
    
    speedSlider.addListener(this);
    
    posSlider.addListener(this);
    
    
    
    volSlider.setRange(0.0, 1.0);
    
    speedSlider.setRange(0.0, 100.0);
    
    posSlider.setRange(0.0, 1.0);
    
    startTimer(500);
 
    
    
    trackName.setReadOnly(true);
    
    trackName.setTextToShowWhenEmpty("No track loaded", juce::Colours::orange);
    
    

}

DeckGUI::~DeckGUI()
{
    
    stopTimer();
    
}

void DeckGUI::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

   // g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
    g.fillAll(juce::Colour::fromRGB(162, 133, 213));

   // g.setColour (juce::Colours::grey);
   // g.setColour (juce::Colour::fromRGB(150,201,162));
    g.setColour (juce::Colour::fromRGB(0,0,0));
    
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
   // g.setColour (juce::Colour::fromRGB(255,255,50));
    
    
    g.setFont (14.0f);
    g.drawText ("DeckGUI", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void DeckGUI::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    
    
  
    
    double rowH = getHeight() / 10;
    
    
    playButton.setBounds(0, 0, getWidth(), rowH);
    
    stopButton.setBounds(0, rowH, getWidth(), rowH);
    
    loadButton.setBounds(0,rowH*2,getWidth(),rowH);
    
    volSlider.setBounds(0, rowH * 2+20, getWidth() / 2, rowH * 4);
    
    speedSlider.setBounds(getWidth()/2, rowH * 2+20, getWidth()/2, rowH * 4);
    
    posSlider.setBounds(60, rowH * 6.8, getWidth() / 2 + 80 , rowH * 1.5);
    
    waveformDisplay.setBounds(0, rowH * 8, getWidth(), rowH * 2);
    
    volSliderLabel.setBounds(75,105,55,50);
    
    speedSliderLabel.setBounds(275,105,50,50);
    
   posSliderLabel.setBounds(0,196,60,60);
    
    
    
    trackName.setColour(juce::TextEditor::backgroundColourId, juce::Colours::transparentBlack);
    
    trackName.setColour(juce::TextEditor::outlineColourId, juce::Colours::transparentBlack);
    
    
    
    
}



void DeckGUI::buttonClicked(juce::Button* button)
{
    
    if(button == &playButton)
    {
        std::cout << "Play button was clicked" << std::endl;
       // transportSource.start();
        player->start();
    }

    if(button == &stopButton)
    {
        std::cout << "Stop button was clicked" << std::endl;
        //transportSource.stop();
        player->stop();
    }


    if (button == &loadButton)
   {

        // this does work in 6.1 but the syntax is a little funky
        // https://docs.juce.com/master/classFileChooser.html#ac888983e4abdd8401ba7d6124ae64ff3
        // - configure the dialogue
//my code        auto fileChooserFlags =
 //my code       juce::FileBrowserComponent::canSelectFiles;
        // - launch out of the main thread
        // - note how we use a lambda function which you've probably
        // not seen before. Please do not worry too much about that.
//my code        fChooser.launchAsync(fileChooserFlags, [this](const juce::FileChooser& chooser)
       //my code        {
       //my code            juce::File chosenFile = chooser.getResult();
            //loadURL(juce::URL{chosenFile});
       //my code            player->loadURL(juce::URL{chooser.getResult()});
            
       //my code            waveformDisplay.loadURL(juce::URL{chooser.getResult()});
            
            //new code 2
       
            //trackName.setText(juce::URL{ chooser.getResult() }.getFileName(), //juce::NotificationType::dontSendNotification);
            //till here 2
       juce::FileChooser chooser{ "Select a file..." };
               if (chooser.browseForFileToOpen()) {
                   player->loadURL(juce::URL{ chooser.getResult() });
                   waveformDisplay.loadURL(juce::URL{ chooser.getResult() });
                   DBG(juce::URL{ chooser.getResult() }.getFileName());

                   trackName.setText(juce::URL{ chooser.getResult() }.getFileName(), juce::NotificationType::dontSendNotification);
               }
           }
       

  //my code      });
// my code    }
    

    
}


void DeckGUI::sliderValueChanged (juce::Slider *slider)
{
    
   
    
    if(slider == &volSlider)
    {
        //std::cout << "vol slider moved " << slider->getValue() <<std::endl;

        //dphase = volSlider.getValue() * 0.01;

        //transportSource.setGain(slider->getValue());

        player->setGain(slider->getValue());
    }

    if(slider == &speedSlider)
    {
       // resampleSource.setResamplingRatio(slider->getValue());
        player->setSpeed(slider->getValue());
    }

    if(slider == &posSlider)
    {

        //player1.setPosition(slider->getValue());
        player->setPositionRelative(slider->getValue());
    }
}



bool DeckGUI::isInterestedInFileDrag(const juce::StringArray &files)
{
    
    std::cout << "DeckGUI::isInterestedInFileDrag" << std::endl;
    
    return true;
}


void DeckGUI::filesDropped(const juce::StringArray &files, int x, int y)
{
    std::cout << "DeckGUI::filesDropped" << std::endl;
    
    if(files.size() == 1)
    {
        player->loadURL(juce::URL{juce::File{files[0]}});
    }
}


void DeckGUI::timerCallback()
{
   // std::cout << "DeckGUI::timerCallback" << std::endl;
    
    
    
    if (std::to_string(loopButton.getToggleState()) == "1") {
        
           if (player->getPositionRelative() >= 1) {
               
               player->setPositionRelative(0);
               
               player->start();
           }
       }

       if (std::to_string(loopButton.getToggleState()) == "0") {
           
           if (player->getPositionRelative() >= 1) {
               
               player->setPositionRelative(0);
               
               player->stop(); 
           }
       }
   
    
    
    
    
    waveformDisplay.setPositionRelative(player->getPositionRelative());
}




void DeckGUI::playlistToDeckGUI() {

      // Opens the textfile which contains the URL for each song in the track
        std::ifstream file("playlist.txt");
    
        std::string str;
    
        std::getline(file, str);
    
        std::string URL = "file:///" + str;
    
        DBG(URL);
    
        juce::URL audioURL{ URL };
    
        player->loadURL(audioURL);
    
        waveformDisplay.loadURL(audioURL);
    
        DBG(audioURL.getFileName());

        mtrackName = audioURL.getFileName();
        
        trackName.setText(mtrackName, juce::NotificationType::dontSendNotification);
        

}


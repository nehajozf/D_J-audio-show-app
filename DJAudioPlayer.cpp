/*
  ==============================================================================

    DJAudioPlayer.cpp
    Created: 9 Feb 2023 6:04:38am
    Author:  Neha Joseph

  ==============================================================================
*/

#include "DJAudioPlayer.h"

DJAudioPlayer::DJAudioPlayer(juce::AudioFormatManager& _formatManager):
                               formatManager(_formatManager)
{
    
}
DJAudioPlayer::~DJAudioPlayer(){
    
}

void DJAudioPlayer::prepareToPlay (int samplesPerBlockExpected, double sampleRate){
    
   // formatManager.registerBasicFormats();
    
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    
}

void DJAudioPlayer::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill){
    
    //transportSource.getNextAudioBlock(bufferToFill);
    
    resampleSource.getNextAudioBlock(bufferToFill);
    
}


void DJAudioPlayer::releaseResources(){
    
    transportSource.releaseResources();
    
    resampleSource.releaseResources();
    
}



void DJAudioPlayer::loadURL(juce::URL audioURL){
    
    auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));
    if (reader != nullptr) // good file
    {
      std::unique_ptr<juce::AudioFormatReaderSource> newSource (new juce::AudioFormatReaderSource (reader, true));
        
        
        
        
        
        
    transportSource.setSource(newSource.get(), 0 , nullptr , reader->sampleRate);
    readerSource.reset (newSource.release());
        
        
        transportSource.start();
        
        
   
    }
    
}


void DJAudioPlayer::setGain(double gain){
    
    if(gain < 0 || gain > 1.0)
    {
        std::cout << "DJAudioPlayer::setGain gain should be in between 0 and 1" << std::endl;
    }
    else
    {
        transportSource.setGain(gain);
    }
    
    
    
}


void DJAudioPlayer::setSpeed(double ratio){
    
    if(ratio < 0 || ratio > 100.0)
    {
        std::cout << "DJAudioPlayer::setSpeed ratio should be in between 0 and 100" << std::endl;
    }
    else
    {
        resampleSource.setResamplingRatio(ratio);
    }
    
}


void DJAudioPlayer::setPosition(double posInSecs){
    
    transportSource.setPosition(posInSecs);
    
}

void DJAudioPlayer::setPositionRelative(double pos){
    
    if(pos < 0 || pos > 1.0)
    {
        std::cout << "DJAudioPlayer::setPositionRelative pos should be in between 0 and 1" << std::endl;
    }
    else
    {
        double posInSecs = transportSource.getLengthInSeconds() * pos;
        setPosition(posInSecs);
    }
    
}


void DJAudioPlayer::start(){
    
    transportSource.start();
    
}


void DJAudioPlayer::stop(){
    
    transportSource.stop();
    
}


double DJAudioPlayer::getPositionRelative()
{
    return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
}

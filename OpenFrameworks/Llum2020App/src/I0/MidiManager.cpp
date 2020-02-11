/*
 *  MidiManager.cpp
 *  Llum 2020 App
 *
 *  Created by Imanol Gomez on 07/02/20.
 *
 */


#include "MidiManager.h"
#include "AppManager.h"


MidiManager::MidiManager(): Manager(), m_channel(1)
{
    //Intentionally left empty
}

MidiManager::~MidiManager()
{
   ofLogNotice() << "MidiManager::destructor";
}


//--------------------------------------------------------------

void MidiManager::setup()
{
    if(m_initialized)
        return;
    
    Manager::setup();
    
    ofLogNotice() <<"MidiManager::initialized" ;
    
    this->setupMidiPorts();
    
}

void MidiManager::setupMidiPorts()
{
	// print input ports to console
	ofLogNotice() << "MidiManager::setupMidiPorts-> Ports: ";
	m_midiOut.listOutPorts(); // via instance
	//ofxMidiIn::listPorts(); // via static as well

	// connect
	m_midiOut.openPort(0); // by number
	//m_midiOut.openPort("IAC Driver Pure Data In"); // by name
	//m_midiOut.openPort("loopMIDI Port"); // by name
	//m_midiOut.openVirtualPort("ofxMidiOut"); // open a virtual port

}

void MidiManager::sendControlChange(int channel, int control, int value)
{
	m_midiOut.sendControlChange(channel, control, value);
}

void MidiManager::sendControlChange(int control, int value)
{
	m_midiOut.sendControlChange(m_channel, control, value);
}

void MidiManager::sendNoteOn(int channel, int pitch, int velocity)
{
	m_midiOut.sendNoteOn(channel, pitch, velocity);
}

void MidiManager::sendNoteOn(int pitch, int velocity)
{
	m_midiOut.sendNoteOn(m_channel, pitch, velocity);
}

void MidiManager::sendNoteOff(int channel, int pitch, int velocity)
{
	m_midiOut.sendNoteOff(channel, pitch, velocity);
}

void MidiManager::sendNoteOff(int pitch, int velocity)
{
	m_midiOut.sendNoteOff(m_channel, pitch, velocity);
}



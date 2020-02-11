/*
 *  MidiManager.h
 *  Llum 2020 App
 *
 *  Created by Imanol Gomez on 07/02/20.
 *
 */


#pragma once

#include "ofxMidi.h"
#include "Manager.h"

//========================== class MidiManager =======================================
//==============================================================================
/** \class MidiManager MidiManager.h
 *	\brief class for managing midi unputs
 *	\details It wraps the ofxMidi addon
 */


class MidiManager: public Manager
{

public:
    //! Constructor
    MidiManager();

    //! Destructor
    virtual ~MidiManager();

    //! setup
    void setup();

	void setMidiCtrlChannel(int value) { m_channel = value; }

	void sendControlChange(int channel, int control, int value);

	void sendControlChange(int control, int value);

	void sendNoteOn(int channel, int pitch, int velocity);

	void sendNoteOn(int pitch, int velocity);

	void sendNoteOff(int channel, int pitch, int velocity);

	void sendNoteOff(int pitch, int velocity);

private:

    //! setups the midi ports
    void setupMidiPorts();


private:


	ofxMidiOut			m_midiOut;		///< Handles Midi input
	int					m_channel;		
   

};


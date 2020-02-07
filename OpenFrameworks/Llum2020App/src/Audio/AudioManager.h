/*
 *  AudioManager.h
 *  Kontrast Moment Dress App
 *
 *  Created by Imanol Gomez on 21/01/20.
 *
 */


#pragma once

#include "ofMain.h"
#include "Manager.h"

#include "ofxFFTLive.h"

//========================== class AudioManager ==============================
//============================================================================
/** \class AudioManager AudioManager.h
 *	\brief Class managing the audio input
 *	\details It reads from the input microphone and calculates the energy.
 */


class AudioManager: public Manager
{
    
public:
    
    //! Constructor
    AudioManager();
    
    //! Destructor
    ~AudioManager();
    
    //! Setup the Audio Manager
    void setup();
    
    //! Update the Audio Manager
    void update();
    
    //! Draw the Audio Manager
    void draw();
    
    void onChangeVolume(float& value);
    
    void onChangeSmoothing(float& value){m_smoothing = value;}

	void onChangeThreshold(float& value) { m_onsetThreshold = value; }

	void onChangeLowLimit(int & value) { m_lowLimit; }

	void onChangeHighLimit(int & value) { m_highLimit; }

	bool getLowOnset() { return m_lowOnset; }
	
	bool getMidOnset() { return m_midOnset; }

	bool getHighOnset() { return m_highOnset; }

	float getLow() { return m_low; }

	float getMid() { return m_mid; }

	float getHigh() { return m_high; }

    
private:
    
    void setupFFT();

	void updateBands();

	void updateOnsets();

	void drawBands();

	void drawFFT();
    
    
private:
    
    float           m_volume;
    int             m_lowLimit, m_highLimit;
	float			m_smoothing;
	float			m_lastLow, m_lastMid, m_lastHigh;
	float			m_low, m_mid, m_high;
	float			m_lowFlux, m_midFlux, m_highFlux;
	float			m_onsetThreshold;
	bool			m_lowOnset, m_highOnset, m_midOnset;
	float			m_width, m_height;


    ofxFFTLive      m_fft;
    
};



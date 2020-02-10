/*
 *  AudioManager.cpp
 *  Kontrast Moment Dress App
 *
 *  Created by Imanol Gomez on 21/01/20.
 *
 */


#include "AppManager.h"
#include "AudioManager.h"


AudioManager::AudioManager() : m_volume(1.0), m_lowLimit(10),
m_highLimit(83), m_smoothing(0.37), m_lastLow(0.0), m_lastMid(0.0), m_lastHigh(0.0),
m_low(0.0), m_mid(0.0), m_high(0.0), m_lowFlux(0.0), m_midFlux(0.0), m_highFlux(0.0),
m_onsetThreshold(0.5), m_lowOnset(false), m_midOnset(false), m_highOnset(false), m_width(100.0f), m_height(100.0f)

{
    //Intentionaly left empty
}


AudioManager::~AudioManager()
{
    ofLogNotice() <<"AudioManager::Destructor" ;
}


void AudioManager::setup()
{
    Manager::setup();
    
    ofLogNotice() <<"AudioManager::initialized" ;
    
    ofLogNotice() <<"AudioManager::setupFFT" ;
    this->setupFFT();
}


void AudioManager::setupFFT()
{
    m_fft.setup();
    m_fft.setMirrorData(false);
    m_fft.setPeakDecay(0.915);
    m_fft.setMaxDecay(0.995);
    m_fft.setThreshold(1.0);
    m_fft.setVolume(m_volume);
   
}


void AudioManager::update()
{
    m_fft.update();
	this->updateBands();
	this->updateOnsets();
    
    //AppManager::getInstance().getOscManager().sendAudioMax(getMaxSound());
    //ofLogNotice() <<"AudioManager::update: " << m_fft.getUnScaledLoudestValue();
    //ofLogNotice() <<"AudioManager::update2: " << m_fft.getLoudBand();
}

void AudioManager::updateBands()
{
	vector<float> normData = m_fft.getFftNormData();

	//separate FFT into bands
	m_low = 0.0;
	int numCounted = 0;
	for(int i = 0; i < m_lowLimit; i++) {
		m_low += (normData[i]* normData[i]);
		numCounted++;
	}

	m_low /= (float)numCounted;
	m_low = sqrt(m_low);

	m_mid = 0.0;
	numCounted = 0;
	for (int i = m_lowLimit; i < m_highLimit; i++) {
		m_mid += (normData[i] * normData[i]);
		numCounted++;
	}

	m_mid /= (float)numCounted;
	m_mid = sqrt(m_mid);

	m_high = 0.0;
	numCounted = 0;
	for (int i = m_highLimit; i < normData.size(); i++) {
		m_high += (normData[i] * normData[i]);
		numCounted++;
	}

	m_high /= (float)numCounted;
	m_high = sqrt(m_mid);

	//smooth values
	m_low = std::max(m_low*m_smoothing + m_lastLow*(1.0f - m_smoothing), m_low);
	m_mid = std::max(m_mid*m_smoothing + m_lastMid * (1.0f - m_smoothing), m_mid);
	m_high = std::max(m_high*m_smoothing + m_lastHigh * (1.0f - m_smoothing), m_high);

	//spectral flux
	m_lowFlux = m_low - m_lastLow;
	m_midFlux = m_mid - m_lastMid;
	m_highFlux = m_high - m_lastHigh;

	//update last values
	m_lastLow = m_low;
	m_lastMid = m_mid;
	m_lastHigh = m_high;

	//Update GUI

	AppManager::getInstance().getGuiManager().setAudioLow(m_low);
	AppManager::getInstance().getGuiManager().setAudioMid(m_mid);
	AppManager::getInstance().getGuiManager().setAudioHigh(m_high);

}

void AudioManager::updateOnsets()
{
	m_lowOnset = m_lowFlux > m_onsetThreshold;
	m_midOnset = m_midFlux > m_onsetThreshold;
	m_highOnset = m_highFlux > m_onsetThreshold;

	AppManager::getInstance().getGuiManager().setAudioLowOnset(m_lowOnset);
	AppManager::getInstance().getGuiManager().setAudioMidOnset(m_midOnset);
	AppManager::getInstance().getGuiManager().setAudioHighOnset(m_highOnset);

}

void AudioManager::triggerLow()
{
	m_lowOnset = true;
	AppManager::getInstance().getGuiManager().setAudioLowOnset(m_lowOnset);
}

void AudioManager::draw()
{
	//this->drawFFT();
	this->drawBands();
	//ofLogNotice() << "Low -> " << m_low;
}

void AudioManager::drawFFT()
{
	m_fft.draw(0,0);
}

void AudioManager::drawBands()
{
	ofPushStyle();

	ofSetColor(ofColor::black);
	ofDrawRectangle(0, 0, m_width, m_height);

	ofSetColor(ofColor::red);
	if (m_lowOnset) ofSetColor(ofColor::white);
	ofDrawRectangle(0, m_height, m_width / 3.0f, -m_low*m_height);

	ofSetColor(ofColor::green);
	if (m_midOnset) ofSetColor(ofColor::white);
	ofDrawRectangle(m_width / 3.0f, m_height, m_width / 3.0f, -m_mid*m_height);

	ofSetColor(ofColor::blue);
	if (m_highOnset) ofSetColor(ofColor::white);
	ofDrawRectangle(2.0f*m_width / 3.0f, m_height, m_width / 3.0f, -m_high*m_height);

	ofPopStyle();
}



void AudioManager::onChangeVolume(float& value)
{
    m_volume = value;
    m_fft.setVolume(m_volume);
}


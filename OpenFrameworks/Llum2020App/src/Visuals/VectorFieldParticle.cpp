/*
 *  VectorFieldParticle.cpp
 *  Llum 2020 App
 *
 *  Created by Imanol Gomez on 05/02/20.
 *
 */

#include "AppManager.h"

#include "VectorFieldParticle.h"

const float VectorFieldParticle:: SCREEN_OFFSET = 2;

VectorFieldParticle::VectorFieldParticle(): m_maxSpeed(2), m_height(10), m_randomness(0.5), m_isUsingTexture(false)
{
    this->setup();
}


VectorFieldParticle::~VectorFieldParticle()
{
    //Intentionaly left empty
}


void VectorFieldParticle::setup(){
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height  = AppManager::getInstance().getSettingsManager().getAppHeight();
    
    m_pos.x = ofRandom(SCREEN_OFFSET,width-SCREEN_OFFSET);
    m_pos.y = ofRandom(SCREEN_OFFSET,height-SCREEN_OFFSET);
    m_prevPos = m_pos;
    //m_color.setHsb(226, 255, 128);
    m_color = ofColor(255);
    
    this->setupBrush();
}

void VectorFieldParticle::reset()
{
	float width = AppManager::getInstance().getSettingsManager().getAppWidth();
	float height = AppManager::getInstance().getSettingsManager().getAppHeight();

	m_pos.x = ofRandom(0, width);
	m_pos.y = ofRandom(0, height);
	m_prevPos = m_pos;
	m_vel = ofVec2f(0);
	m_acc = ofVec2f(0);

}

void VectorFieldParticle::setupBrush()
{
    m_brush.setResource("Dot");
    m_brush.setCentred(true);
    m_brush.setWidth(m_height,true);
}


void VectorFieldParticle::setSize(float size)
{
     m_height = size;
     m_brush.setWidth(m_height,true);
}

void VectorFieldParticle::addForce(const ofVec2f& dir)
{
    m_acc += dir;
}



void VectorFieldParticle::update()
{
    //float height  = AppManager::getInstance().getSettingsManager().getAppHeight();
    
    m_vel+=m_acc;
    m_vel.limit(m_maxSpeed);
    m_prevPos = m_pos;
    m_pos+= (m_vel + ofVec2f(ofRandom(-m_randomness,m_randomness),ofRandom(-m_randomness,m_randomness)));
    m_acc = ofVec2f(0);
    
    
    if(this->isOffScreen()){
        this->stayOnScreen();
         m_prevPos = m_pos;
    }
    
    this->stayOnScreen();
    
    m_brush.setPosition(m_pos);
    m_brush.setColor(m_color);
}

void VectorFieldParticle::draw(){
    ofPushMatrix();
    ofPushStyle();
        m_brush.draw();
    ofPopStyle();
    ofPopMatrix();
}

void VectorFieldParticle::stayOnScreen()
{
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height  = AppManager::getInstance().getSettingsManager().getAppHeight();
    
    if( m_pos.x < - SCREEN_OFFSET ) m_pos.x = width - SCREEN_OFFSET;
    if( m_pos.x > width + SCREEN_OFFSET) m_pos.x = SCREEN_OFFSET;
    
    if( m_pos.y < - SCREEN_OFFSET ) m_pos.y = height - SCREEN_OFFSET;
    if( m_pos.y > height + SCREEN_OFFSET ) m_pos.y = SCREEN_OFFSET;
    
}

bool VectorFieldParticle::isOffScreen(){
    
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height  = AppManager::getInstance().getSettingsManager().getAppHeight();
    
    if( m_pos.x <  - SCREEN_OFFSET || m_pos.x > width + SCREEN_OFFSET|| m_pos.y < - SCREEN_OFFSET || m_pos.y > height +  SCREEN_OFFSET ){
        
        return true;
    }
    
    return false;
}


void VectorFieldParticle::setUseTexture(bool value)
{
    m_isUsingTexture = value;
    if(m_isUsingTexture){
        m_brush.setResource("Brush");
    }
    
}


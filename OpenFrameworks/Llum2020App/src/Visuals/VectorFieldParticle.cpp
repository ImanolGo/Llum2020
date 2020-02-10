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

VectorFieldParticle::VectorFieldParticle(): m_maxSpeed(2), m_size(10), m_randomness(0.5), m_isUsingTexture(false)
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
	float hue = ofRandom(255);
    //m_color.setHsb(hue, 255, 255);
    m_color = ofColor::white;
    
    this->setupBrush();
}

void VectorFieldParticle::reset()
{
	float width = AppManager::getInstance().getSettingsManager().getAppWidth();
	float height = AppManager::getInstance().getSettingsManager().getAppHeight();

	m_pos.x = ofRandom(0, width);
	m_pos.y = ofRandom(0, height);
	m_prevPos = m_pos;
	m_vel = glm::vec3(0);
	m_acc = glm::vec3(0);

}

void VectorFieldParticle::setupBrush()
{
    m_brush.setResource("Dot");
    m_brush.setCentred(true);
    m_brush.setWidth(m_size,true);
}


void VectorFieldParticle::setSize(float size)
{
	m_size = size;
     m_brush.setWidth(m_size,true);
}

void VectorFieldParticle::addForce(const glm::vec3& dir)
{
    m_acc += dir;
}



void VectorFieldParticle::update()
{
    //float height  = AppManager::getInstance().getSettingsManager().getAppHeight();
    
    m_vel+=m_acc;
	//m_vel = glm::clamp(m_vel, glm::vec3(0), glm::vec3(m_maxSpeed));
	this->limit(m_vel, m_maxSpeed);
    //m_vel.limit(m_maxSpeed);
    m_prevPos = m_pos;
    m_pos+= (m_vel + glm::vec3(ofRandom(-m_randomness,m_randomness),ofRandom(-m_randomness,m_randomness), 0.0));
    m_acc = glm::vec3(0);
    
    
    if(this->isOffScreen()){
        this->stayOnScreen();
         m_prevPos = m_pos;
    }
    
    this->stayOnScreen();
    
    m_brush.setPosition(m_pos);
    m_brush.setColor(m_color);
}

void VectorFieldParticle::limit(glm::vec3& vec, float max) {
	float lengthSquared = glm::length(vec);
	if (lengthSquared > max*max && lengthSquared > 0) {
		float ratio = max / (float)sqrt(lengthSquared);
		vec *= ratio;
	}
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


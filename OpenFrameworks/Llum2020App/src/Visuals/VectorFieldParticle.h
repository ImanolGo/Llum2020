/*
 *  VectorFieldParticle.h
 *  Llum 2020 App
 *
 *  Created by Imanol Gomez on 05/02/20.
 *
 */

#pragma once

#include "ofMain.h"
#include "ImageVisual.h"

//======================== class VectorFieldParticle =========================
//============================================================================
/** \class VectorFieldParticle VectorFieldParticle.h
 *    \brief Class definding a vector field particle
 *    \details It describes the behaviour and rendering of a vector field particle
 */

class VectorFieldParticle
{
    static const float SCREEN_OFFSET;

public:
    
    //! Constructor
    VectorFieldParticle();
    
    //! Destructor
    ~VectorFieldParticle();
    
    //! Update the Vector Field Particle
    void update();
    
    //! Draw the Vector Field Particle
    void draw();
    
    void addForce(const ofVec2f& dir);
    
    void setRandomness(float value) {m_randomness = value;}
    
    void setMaxSpeed(float speed) {m_maxSpeed = speed;}
    
    void setSize(float size);
    
    ofVec2f getPos() const {return m_pos;}

	void reset();
    
    void setColor(ofColor& color) {m_color = color;}
    
    void setUseTexture(bool value);
    
private:
    
    //! Setup the Vector Field Particle
    void setup();
    
    void setupBrush();
    
    bool isOffScreen();
    
    void stayOnScreen();
    
private:
    
    ofVec2f     m_pos;
    ofVec2f     m_prevPos;
    ofVec2f     m_vel;
    ofVec2f     m_acc;
    float       m_maxSpeed;
    
    ofColor     m_color;
    ImageVisual m_brush;
    
    bool        m_isUsingTexture;
    
    
    int     m_duration;
    float   m_height;
    float   m_randomness;
};

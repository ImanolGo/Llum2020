/*
 *  VectorFieldVisual.h
 *  Llum 2020 App
 *
 *  Created by Imanol Gomez on 05/02/20.
 *
 */
#pragma once

#include "ofxVectorField.h"
#include "VectorFieldParticle.h"
#include "ParticlesManager.h"

#define radian2degree(a) (a * 57.295779513082)
#define degree2radian(a) (a * 0.017453292519)


//========================= class VectorFieldVisual ==========================
//============================================================================
/** \class VectorFieldVisual VectorFieldVisual.h
 *	\brief Class managing the vector field visuals
 *	\details It creates and manages all the parameters and vector field like visualizations
 */


class VectorFieldVisual
{
    static const int NUM_PARTICLES;

    
public:
    
    //! Constructor
    VectorFieldVisual();
    
    //! Destructor
    ~VectorFieldVisual();
    
    //! Setup the Vector Field Visual
    void setup();
    
    //! Update the Vector Field Visual
    void update();
    
    //! Draw the Vector Field Visual
    void draw();
    
    void addForce(const glm::vec3& force);
    
    void addParameters(ParticleParameters& parameters);
    
    void setSpeed(float value);
    
    void setVectSpeed(float value) {m_speed = value;}
    
    void setSize(float value);
    
    void setRandomness(float value);
    
    void setNumber(int value);

	void resetParticles();
    
    void setFadeTime(float& value) {m_fadeTime = value;}
    
    int getNumParticles() const {return m_particles.size();}
    
    void setColor(int index, ofColor& color);
    
    void setAdditiveBlend(bool value);
    
private:
    
    void setupVectorField();

	void setupShader();
    
    void setupFbo();
     
    void setupParticles();
    
    void updateFbo();
    
    void updateVectorField();
    
    void updateParticles();
    
    void drawVectorField();
    
    void drawParticles();
    
    
private:
    
    ofxVectorField                 m_vectorField;
    vector <VectorFieldParticle>   m_particles;

	vector <glm::vec3>       m_points;
	vector <glm::vec3>       m_sizes;
	vector <ofFloatColor>	 m_colors;
    
    float       m_spacing;
    float       m_speed;
    float       m_fadeTime;
    int         m_skipFrames;
    
    ofFbo       m_fbo;
    int         m_numParticles;
    float       m_size;
    bool        m_isAdditiveBlend;

	ofVbo                  m_vbo;
	ofShader               m_shader;
	ofShader			m_vboShader;
	ofTexture			m_texture;

};




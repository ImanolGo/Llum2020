/*
 *  VectorFieldVisual.cpp
 *  Llum 2020 App
 *
 *  Created by Imanol Gomez on 05/02/20.
 *
 */


#include "AppManager.h"
#include "VectorFieldVisual.h"

const int VectorFieldVisual::NUM_PARTICLES = 1500;


VectorFieldVisual::VectorFieldVisual():m_speed(0.02), m_spacing(20), m_skipFrames(0), m_fadeTime(8), m_size(20), m_isAdditiveBlend(false)
{
    //Intentionaly left empty
}


VectorFieldVisual::~VectorFieldVisual()
{
    //Intentionaly left empty
}


void VectorFieldVisual::setup()
{
    this->setupFbo();
	this->setupShader();
    this->setupVectorField();
    this->setupParticles();

	ofLogNotice() << "VectorFieldVisual::setup"; 
}


void VectorFieldVisual::setupFbo()
{
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height  = AppManager::getInstance().getSettingsManager().getAppHeight();
    m_fbo.allocate(width,height, GL_RGBA32F_ARB);
	//m_fbo.allocate(width, height, GL_RGB);
    m_fbo.begin(); ofClear(0); m_fbo.end();
}

void VectorFieldVisual::setupShader()
{
	ofLogNotice() << "LedGroup::setupShader ";
	ofFile file;
	string texture1 = "images/general/dot.png";

	
	m_vboShader.load("shaders/vboShader");

	ofDisableArbTex();
	ofLoadImage(m_texture, texture1);
	ofEnableArbTex();
}

void VectorFieldVisual::setupVectorField()
{
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height  = AppManager::getInstance().getSettingsManager().getAppHeight();
    
    m_vectorField.setup(width,height, m_spacing);
    
    // create the vector field using perlin noise
    m_vectorField.randomize();
    
    // adjust the vector field by normalizing, scaling, biasing & blurring (to make it look nice)
    m_vectorField.normalize();
    m_vectorField.scale(40);
    m_vectorField.bias(1, 1);
    //m_vectorField.blur();
}

void VectorFieldVisual::setupParticles()
{
	m_points.clear();
	m_sizes.clear();
	m_colors.clear();

	//int   num = 500;
	//float radius = 1000;
	//for (int i = 0; i < num; i++) {

	//	float theta1 = ofRandom(0, TWO_PI);
	//	float theta2 = ofRandom(0, TWO_PI);

	//	glm::vec3 p;
	//	p.x = cos(theta1) * cos(theta2);
	//	p.y = sin(theta1);
	//	p.z = cos(theta1) * sin(theta2);
	//	p *= radius;


	//	m_points.push_back(p);
	//	 we are passing the size in as a normal x position
	//	float size = ofRandom(5, 50);

	//	m_sizes.push_back(glm::vec3(size));

	//}



   for( int i=0; i<NUM_PARTICLES; i++)
    {
        m_particles.push_back(VectorFieldParticle());
		m_sizes.push_back(ofVec3f(m_particles.back().getSize()));
		m_points.push_back(m_particles.back().getPos());
		m_colors.push_back(m_particles.back().getColor());
    }

	// upload the data to the vbo
	//int total = (int)m_points.size();
	//m_vbo.setVertexData(&m_points[0], total, GL_DYNAMIC_DRAW);
	//m_vbo.setNormalData(&m_sizes[0], total, GL_DYNAMIC_DRAW);
	//m_vbo.setColorData(&m_colors[0], total, GL_DYNAMIC_DRAW);
}

void VectorFieldVisual::resetParticles()
{
	m_fbo.begin(); ofClear(0); m_fbo.end();

	for (int i = 0; i < m_particles.size(); i++)
	{
		m_particles[i].reset();
	}
}
    


void VectorFieldVisual::update()
{
    this->updateVectorField();
    this->updateParticles();
    this->updateFbo();
}

void VectorFieldVisual::updateVectorField()
{
    m_vectorField.animate(m_speed);
}

void VectorFieldVisual::updateParticles()
{
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height  = AppManager::getInstance().getSettingsManager().getAppHeight();


    for( int i=0; i<m_particles.size(); i++)
    {
		if (i< m_numParticles) {
			auto force = m_vectorField.getVectorInterpolated(m_particles[i].getPos().x, m_particles[i].getPos().y, width, height*1.2);
			m_particles[i].addForce(glm::vec3(force.x, force.y, 0.0));
			m_particles[i].update();
			m_points[i] = m_particles[i].getPos();
			m_sizes[i] = ofVec3f(m_particles[i].getSize());
			m_colors[i] = m_particles[i].getColor();
		}
		else {
			m_sizes[i] = ofVec3f(0);
		}
    }

	//m_vbo.setVertexData(&m_points[0], (int)m_points.size(), GL_DYNAMIC_DRAW);
	//m_vbo.setNormalData(&m_sizes[0], (int)m_sizes.size(), GL_DYNAMIC_DRAW);
	//m_vbo.setColorData(&m_colors[0], (int)m_colors.size(), GL_DYNAMIC_DRAW);
}

void VectorFieldVisual::updateFbo()
{
	float fadeAmnt = 10.0;
	float framesToDie = 255.0 / fadeAmnt;
	float dt = ofGetLastFrameTime();
	int numSkipFrames = m_fadeTime / (framesToDie*dt);
	m_skipFrames++;
    
	ofEnableAlphaBlending();
	//ofEnableBlendMode(OF_BLENDMODE_ALPHA);

    m_fbo.begin();
 
	if (m_skipFrames >= numSkipFrames) {
		
		ofSetColor(0, fadeAmnt);
		ofFill();
		ofDrawRectangle(0, 0, m_fbo.getWidth(), m_fbo.getHeight());
		m_skipFrames = 0;
	}

        this->drawParticles();
   
     m_fbo.end();
    //ofDisableAlphaBlending();
    //ofDisableBlendMode();
}

void VectorFieldVisual::draw()
{
	m_fbo.draw(0, 0);
}


void VectorFieldVisual::drawVectorField()
{
    m_vectorField.draw();
}

void VectorFieldVisual::drawParticles()
{
	//ofEnableSmoothing();
    
    ofEnableAlphaBlending();
    
    if(m_isAdditiveBlend){
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        for( int i=0; i<m_numParticles; i++){
            m_particles[i].draw();
        }
  
    }
    else{
        for( int i=0; i<m_numParticles; i++){
            m_particles[i].draw();
        }
    }

	//if (m_isAdditiveBlend) {
	//	ofEnableBlendMode(OF_BLENDMODE_ADD);
	//}

	//ofEnablePointSprites();
	//m_shader.begin();
	//m_texture.bind();
	//m_vbo.draw(GL_POINTS, 0, (int)m_points.size());
	//m_texture.unbind();
	//m_shader.end();
	//ofDisablePointSprites();
	//ofDisableBlendMode();

	ofDisableBlendMode();
}


void VectorFieldVisual::addParameters(ParticleParameters& parameters)
{
     m_size = parameters.size;
    
    for( int i=0; i<m_particles.size(); i++){
        m_particles[i].setUseTexture(m_isAdditiveBlend);
        m_particles[i].setMaxSpeed(parameters.speed);
        m_particles[i].setSize(m_size*2);
        m_particles[i].setRandomness(parameters.randomness);
        
    }
  
    m_numParticles = (int) ofClamp(parameters.num, 0, m_particles.size());
    m_fadeTime = parameters.fadeTime;
    //m_speed = parameters.vectorSpeed;
}

void VectorFieldVisual::setColor(int index, ofColor& color)
{
    if(index<0 || index>= m_particles.size()){
        return;
    }
    
    m_particles[index].setColor(color);
    
}

void VectorFieldVisual::addForce(const glm::vec3& force)
{
    for( int i=0; i<m_particles.size(); i++){
        m_particles[i].addForce(force);
    }
}

void VectorFieldVisual::setSpeed(float value)
{
    for( int i=0; i<m_particles.size(); i++){
        m_particles[i].setMaxSpeed(value);
    }
}

void VectorFieldVisual::setSize(float value)
{
    for( int i=0; i<m_particles.size(); i++){
        m_particles[i].setSize(value);
    }
}

void VectorFieldVisual::setRandomness(float value)
{
    for( int i=0; i<m_particles.size(); i++){
        m_particles[i].setRandomness(value);
    }
}

void VectorFieldVisual::setNumber(int value)
{
    m_numParticles = min(value,(int)m_particles.size());
    m_numParticles = max(m_numParticles,0);
}

void VectorFieldVisual::setAdditiveBlend(bool value)
{
    m_isAdditiveBlend = value;
    for( int i=0; i<m_particles.size(); i++){
        m_particles[i].setUseTexture(value);
    }
}


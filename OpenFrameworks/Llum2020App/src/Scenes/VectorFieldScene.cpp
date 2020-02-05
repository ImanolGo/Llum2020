/*
 *  VectorFieldScene.cpp
 *  Llum 2020 App
 *
 *  Created by Imanol Gomez on 05/02/20.
 *
 */



#include "AppManager.h"
#include "VectorFieldScene.h"

VectorFieldScene::VectorFieldScene(string name): ofxScene(name)
{
     //Intentionally left empty
}

void VectorFieldScene::setup() {
    ofLogNotice(getName() + "::setup");
    this->setupVectorField();
    this->setupFbo();
}


void VectorFieldScene::setupVectorField()
{
    m_vectorField.setup();
}

void VectorFieldScene::setupFbo()
{
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height = AppManager::getInstance().getSettingsManager().getAppHeight();
    
    m_fbo.allocate(width, height);
    m_fbo.begin(); ofClear(0); m_fbo.end();
}


void VectorFieldScene::update() {
    
    this->updateVectorField();
    this->updateFbo();
    
}

void VectorFieldScene::updateVectorField()
{
    auto parameters = AppManager::getInstance().getParticlesManager().getParameters();
    float angleRadiands = degree2radian(parameters.direction);

    ofVec2f force;
    force.x = -parameters.directionMag*sin(angleRadiands);
    force.y = parameters.directionMag*cos(angleRadiands);
    m_vectorField.addForce(force);


    m_vectorField.addParameters(parameters);    
    m_vectorField.update();
}


void VectorFieldScene::updateFbo()
{
    m_fbo.begin();
    ofClear(0);
    this->drawVectorField();
    m_fbo.end();
}

void VectorFieldScene::draw()
{
    ofClear(0);
    //ofBackground(color);
    m_fbo.draw(0,0);
}

void VectorFieldScene::drawVectorField()
{
    m_vectorField.draw();
}

 void VectorFieldScene::setAdditiveBlend(bool value)
{
    m_vectorField.setAdditiveBlend(value);
}

void VectorFieldScene::willFadeIn() {
    ofLogNotice("VectorFieldScene::willFadeIn");
	AppManager::getInstance().getGuiManager().loadPresets(this->getName());
    m_vectorField.resetParticles();
    
}

void VectorFieldScene::willDraw() {
    ofLogNotice("VectorFieldScene::willDraw");
}

void VectorFieldScene::willFadeOut() {
    ofLogNotice("VectorFieldScene::willFadeOut");
	AppManager::getInstance().getGuiManager().savePresets(this->getName());
}

void VectorFieldScene::willExit() {
    ofLogNotice("VectorFieldScene::willExit");
}

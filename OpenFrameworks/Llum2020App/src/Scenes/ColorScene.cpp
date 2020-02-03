/*
 *  ColorScene.cpp
 *  Llum 2020 App
 *
 *  Created by Imanol Gomez on 01/02/20.
 *
 */


#include "ColorScene.h"
#include "AppManager.h"

ColorScene::ColorScene(): ofxScene("Color"), m_initialized(false)
{
    //Intentionally left empty
}

ColorScene::~ColorScene()
{
    //Intentionally left empty
}


void ColorScene::setup() {
    
    if(m_initialized){
        return;
    }
    
    
    ofLogNotice(getName() + "::setup");
    this->setupFbo();
    
    m_initialized = true;
}

void ColorScene::setupFbo()
{
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height = AppManager::getInstance().getSettingsManager().getAppHeight();
    
	m_fbo.allocate(width, height, GL_RGBA);
	m_fbo.begin(); ofClear(0, 0, 0, 0); m_fbo.end();
}


void ColorScene::update()
{
    this->updateFbo();
}

void ColorScene::updateFbo()
{
    auto floatColor = AppManager::getInstance().getColorManager().getSolidColor();
    //auto color = ofColor(floatColor.b*255, floatColor.g*255, floatColor.b*255 );
   // m_rectangle.setColor(floatColor);

	m_fbo.begin();
		ofSetColor(floatColor);
		ofDrawRectangle(0, 0,  m_fbo.getWidth(), m_fbo.getHeight());
	m_fbo.end();
    
}


void ColorScene::draw()
{

	this->drawFbo();
}

void ColorScene::drawFbo()
{
    m_fbo.draw(0,0);
}

void ColorScene::willFadeIn() {
     ofLogNotice("ColorScene::willFadeIn");
     AppManager::getInstance().getGuiManager().setColorCorrectionType(0);
	 AppManager::getInstance().getGuiManager().loadPresets(this->getName());
}

void ColorScene::willDraw() {
    ofLogNotice("ColorScene::willDraw");
}

void ColorScene::willFadeOut() {
	AppManager::getInstance().getGuiManager().savePresets(this->getName());
    ofLogNotice("ColorScene::willFadeOut");
}

void ColorScene::willExit() {
    ofLogNotice("ColorScene::willExit");
}

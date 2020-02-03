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
    
    m_initialized = true;
}


void ColorScene::update()
{
    //
}


void ColorScene::draw()
{
	float width = AppManager::getInstance().getSettingsManager().getAppWidth();
	float height = AppManager::getInstance().getSettingsManager().getAppHeight();
	auto & floatColor = AppManager::getInstance().getColorManager().getSolidColor();

	ofPushStyle();
		ofSetColor(floatColor);
		ofDrawRectangle(0,0, width, height);
	ofPopStyle();
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

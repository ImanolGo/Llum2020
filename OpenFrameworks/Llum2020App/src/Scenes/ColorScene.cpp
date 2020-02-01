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
    this->setupRectangle();
    
    m_initialized = true;
}

void ColorScene::setupRectangle()
{
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height = AppManager::getInstance().getSettingsManager().getAppHeight();
    
    m_rectangle = RectangleVisual(ofPoint(0), width, height, false);
}


void ColorScene::update()
{
    this->updateRectangle();
}

void ColorScene::updateRectangle()
{
    auto floatColor = AppManager::getInstance().getColorManager().getSolidColor();
    //auto color = ofColor(floatColor.b*255, floatColor.g*255, floatColor.b*255 );
   // m_rectangle.setColor(floatColor);
    m_rectangle.setColor(ofColor::white);
    
}


void ColorScene::draw()
{
    ofBackground(0,0,0);
    this->drawRectangle();
}

void ColorScene::drawRectangle()
{
    m_rectangle.draw();
}

void ColorScene::willFadeIn() {
     ofLogNotice("ColorScene::willFadeIn");
     AppManager::getInstance().getGuiManager().setColorCorrectionType(1);
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

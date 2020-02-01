/*
 *  ImageScene.cpp
 *  Llum 2020 App
 *
 *  Created by Imanol Gomez on 01/02/20.
 *
 */


#include "ImageScene.h"
#include "AppManager.h"

ImageScene::ImageScene(std::string name): ofxScene(name), m_initialized(false)
{
    //Intentionally left empty
}

ImageScene::~ImageScene()
{
    //Intentionally left empty
}


void ImageScene::setup() {
    
    if(m_initialized){
        return;
    }
    
    
    ofLogNotice(getName() + "::setup");
    this->setupImage();
    
    m_initialized = true;
}

void ImageScene::setupImage()
{
   
    m_texture = AppManager::getInstance().getResourceManager().getTexture(getName());
}


void ImageScene::update()
{
    //
}


void ImageScene::draw()
{
    ofBackground(0,0,0);
    this->drawImage();
}

void ImageScene::drawImage()
{
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height = AppManager::getInstance().getSettingsManager().getAppHeight();
    
    if(m_texture){
        m_texture->draw(0,0,width, height);
    }
    
}

void ImageScene::willFadeIn() {
     ofLogNotice("ImageScene::willFadeIn");
     AppManager::getInstance().getGuiManager().setColorCorrectionType(0);
	 AppManager::getInstance().getGuiManager().loadPresets(this->getName());
}

void ImageScene::willDraw() {
    ofLogNotice("ImageScene::willDraw");
}

void ImageScene::willFadeOut() {
    ofLogNotice("ImageScene::willFadeOut");
	AppManager::getInstance().getGuiManager().savePresets(this->getName());
}

void ImageScene::willExit() {
    ofLogNotice("ImageScene::willExit");
}

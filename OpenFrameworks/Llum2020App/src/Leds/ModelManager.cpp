/*
 *  ModelManager.cpp
 *  Llum 2020 App
 *
 *  Created by Imanol Gomez on 01/02/20.
 *
 */


#include "ofMain.h"

#include "ModelManager.h"
#include "AppManager.h"


ModelManager::ModelManager(): Manager()
{
	//Intentionally left empty
}


ModelManager::~ModelManager()
{
    ofLogNotice() <<"ModelManager::Destructor" ;
}



void ModelManager::setup()
{
	if(m_initialized)
		return;

    ofLogNotice() <<"ModelManager::initialized" ;

	Manager::setup();
    
    this->setupPostProcessing();
    this->resetCamera();
}

void ModelManager::setupPostProcessing()
{
    
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height = AppManager::getInstance().getSettingsManager().getAppHeight();
    
    m_postProcessing.init(width, height);
    m_postProcessing.createPass<BloomPass>()->setEnabled(true);
}


void ModelManager::resetCamera()
{
    m_camera.reset();
    m_camera.setDistance(100);
    //m_camera.enableInertia();
    //m_camera.setAutoDistance(true);
}


void ModelManager::update()
{
    
}

void ModelManager::draw()
{
    string name = "3D";
    //auto rect = AppManager::getInstance().getLayoutManager().getWindowRect(name);
    
    //ofRectangle rect2 = ofRectangle(rect->x, rect->y, 0, 0);
    
    ofBackgroundGradient( ofColor(100), ofColor(15), OF_GRADIENT_CIRCULAR );

	ofEnableAlphaBlending();
    ofDisableArbTex();
    glDepthMask(GL_FALSE);
    
    //ofSetColor(255, 100, 90);
    
    // this makes everything look glowy :)
    //ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofEnablePointSprites();
    
    //ofEnableDepthTest();
    //ofTranslate(-rect->x, 0, 0);
    m_camera.begin();
    //m_postProcessing.begin(m_camera);
   // ofTranslate(-rect->x, 0, 0);
    //this->drawLeds();
    
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    AppManager::getInstance().getLedsManager().drawModel();
    
    //ofEnableBlendMode(OF_BLENDMODE_ADD);
    AppManager::getInstance().getLedsManager().draw();
    
   // ofTranslate(rect->x, 0 , 0);
    m_camera.end();
    //m_postProcessing.end();
    ofDisablePointSprites();
    ofEnableArbTex();
    
}

void ModelManager::setControlArea(ofRectangle& rect)
{
    m_camera.setControlArea(rect);
    m_postProcessing.init(rect.getWidth(), rect.getHeight());
    
}


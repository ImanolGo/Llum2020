/*
 *  ShaderScene.cpp
 *  Llum 2020 App
 *
 *  Created by Imanol Gomez on 01/02/20.
 *
 */

#include "ShaderScene.h"
#include "AppManager.h"

ShaderScene::ShaderScene(std::string name): ofxScene(name), m_initialized(false), m_elapsedTime(0.0), m_targetAddedSpeed(0.0), m_addedSpeed(0.0)
{
    //Intentionally left empty
}

ShaderScene::~ShaderScene()
{
   //Intentionally left empty
}


void ShaderScene::setup() {
    
    if(m_initialized){
        return;
    }
        
    ofLogNotice(getName() + "::setup");
    this->setupShader();
    this->setupFbo();
    
    m_initialized = true;
}



void ShaderScene::setupFbo()
{
    float resolution = 0.5;
    float width = AppManager::getInstance().getSettingsManager().getAppWidth()*resolution;
    float height = AppManager::getInstance().getSettingsManager().getAppHeight()*resolution;
    m_fbo.allocate(width, height);
    m_fbo.begin(); ofClear(0); m_fbo.end();
}
void ShaderScene::setupShader()
{
    ofLogNotice() << getName() + "::setupShader";
    
    string path = "shaders/" + getName();
    
    m_shader.unload();
    if(m_shader.load(path))
    {
        ofLogNotice() << getName() + "::setupShader-> successfully loaded " << path;
    }
    else{
         ofLogNotice() << getName() + "::setupShader-> Cannot load " << path;
    }
}


void ShaderScene::update()
{
	this->updateSpeed();
    this->updateTime();
    this->updateFbo();
}


void ShaderScene::updateSpeed()
{
	bool isOnset = AppManager::getInstance().getAudioManager().getLowOnset();
	float speed = AppManager::getInstance().getGuiManager().getShaderSpeed();
	if (isOnset) {
		m_addedSpeed = speed*3;
	}
	
	m_addedSpeed = m_addedSpeed + (m_targetAddedSpeed - m_addedSpeed)*0.06f;
}

void ShaderScene::updateTime()
{
    float speed = AppManager::getInstance().getGuiManager().getShaderSpeed();
    m_elapsedTime += (ofGetLastFrameTime()* (speed + m_addedSpeed));
    if(m_elapsedTime<0){
        m_elapsedTime = 0;
    }
    
}

void ShaderScene::updateFbo()
{
    m_fbo.begin();
    ofClear(0,255);
    this->drawShader();
    m_fbo.end();
}

void ShaderScene::draw()
{
     //ofEnableArbTex();
    ofBackground(0,0,0);
	AppManager::getInstance().getColorManager().beginColorCorrection();
    this->drawFbo();
	AppManager::getInstance().getColorManager().endColorCorrection();
}

void ShaderScene::drawFbo()
{
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height = AppManager::getInstance().getSettingsManager().getAppHeight();
    m_fbo.draw(0,0, width, height);
}


void ShaderScene::drawShader()
{
    float width = m_fbo.getWidth();
    float height = m_fbo.getHeight();
    auto floatColor = AppManager::getInstance().getColorManager().getSolidColor();
    float parameter = AppManager::getInstance().getGuiManager().getShaderParameter();
    int direction = AppManager::getInstance().getGuiManager().getShaderDirection();
    float colorAmount = AppManager::getInstance().getGuiManager().getColorAmount();
    
    m_shader.begin();
    //m_shader.setUniform4f("iColor", floatColor);
    m_shader.setUniform1f("iGlobalTime", m_elapsedTime);
    m_shader.setUniform3f("iResolution", width, height,0.0);
    m_shader.setUniform1f("parameter", parameter);
    m_shader.setUniform1i("direction", direction);
    m_shader.setUniform1f("colorAmount", colorAmount);
    
    ofDrawRectangle(0, 0, width, height);
    m_shader.end();
}

void ShaderScene::willFadeIn() {
     this->setupShader();
     ofLogNotice("ShaderScene::willFadeIn");
     AppManager::getInstance().getGuiManager().setColorCorrectionType(1);
	 AppManager::getInstance().getGuiManager().loadPresets(this->getName());
    
}

void ShaderScene::willDraw() {
    ofLogNotice("ShaderScene::willDraw");
}

void ShaderScene::willFadeOut() {
    ofLogNotice("ShaderScene::willFadeOut");
	AppManager::getInstance().getGuiManager().savePresets(this->getName());
}

void ShaderScene::willExit() {
    ofLogNotice("ShaderScene::willExit");
}

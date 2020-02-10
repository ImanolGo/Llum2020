/*
 *  SwipeScene.cpp
 *  Llum 2020 App
 *
 *  Created by Imanol Gomez on 10/02/20.
 *
 */


#include "SwipeScene.h"
#include "AppManager.h"

SwipeVisual::SwipeVisual(const ofVec3f& pos, const string& resourceName, float lifetime) : ImageVisual(pos, resourceName, true),m_timeLeft(0), m_isAlive(true)
{
	this->setLifetime(lifetime);
}

SwipeVisual::~SwipeVisual()
{
	//Intentionally left empty
}

void SwipeVisual::update() {

	if (!m_isAlive) {
		return;
	}

	double dt = ofGetLastFrameTime();
	m_timeLeft -= dt;

	if (m_timeLeft < 0) {
		m_isAlive = false;
	}
}

void SwipeVisual::setLifetime(float lifetime)
{
	if (lifetime > 0) {
		m_isAlive = true;
		m_timeLeft = lifetime;
	}
}


SwipeScene::SwipeScene(): ofxScene("SwipeScene")
{
    //Intentionally left empty
}

SwipeScene::~SwipeScene()
{
   //Intentionally left empty
}


void SwipeScene::setup() 
{
    
    ofLogNotice("SwipeScene::setup");
	this->deleteSwipes();
    
}


void SwipeScene::update()
{
	this->updateTrigger();
    this->updateSwipes();

}

void SwipeScene::updateTrigger()
{
	bool isOnset = AppManager::getInstance().getAudioManager().getLowOnset();
	if (isOnset) {
		this->startSwipe();
	}
}

void SwipeScene::updateSwipes()
{
	for (SwipesVector::iterator it = m_swipes.begin(); it != m_swipes.end();)
	{
		(*it)->update();

		if (!(*it)->isAlive()) {
			AppManager::getInstance().getVisualEffectsManager().removeAllVisualEffects((*it));
			it = m_swipes.erase(it);
			ofLogNotice() << "SwipeScene::updateAnimations -> Number: " << m_swipes.size();
		}
		else {
			++it;
		}
	}
}

void SwipeScene::draw()
{	
	float width = AppManager::getInstance().getSettingsManager().getAppWidth();
	float height = AppManager::getInstance().getSettingsManager().getAppHeight();

	ofClear(0);
	
	AppManager::getInstance().getColorManager().beginColorCorrection();

	ofSetColor(0);
	ofDrawRectangle(0, 0, width, height);
	ofSetColor(255);
	this->drawSwipes();

	AppManager::getInstance().getColorManager().endColorCorrection();
}

void SwipeScene::drawSwipes()
{

    for(auto swipe: m_swipes){
		swipe->draw();
    }
}

void SwipeScene::deleteSwipes()
{
    for(auto swipe : m_swipes){
        AppManager::getInstance().getVisualEffectsManager().removeAllVisualEffects(swipe);
    }

	m_swipes.clear();

}

void SwipeScene::startSwipe()
{
	float animationTime = 3.0*AppManager::getInstance().getGuiManager().getShaderSpeed();
	EffectSettings settings;
	settings.function = SINUSOIDAL;
	settings.startAnimation = 0.0;
	settings.animationTime = animationTime;

	if (ofRandomf() > 0) {
		this->startSwipeRing(settings);
	}
	else {
		this->startSwipeRectangle(settings);
	}
    
}

void SwipeScene::startSwipeRing(EffectSettings& settings)
{
	float width = AppManager::getInstance().getSettingsManager().getAppWidth();
	float height = AppManager::getInstance().getSettingsManager().getAppHeight();

	string resourceName = "RingSwipe";
	glm::vec3 pos(width*0.5, height*0.5, 0);
	shared_ptr<SwipeVisual> swipe = make_shared<SwipeVisual>(pos, resourceName, settings.animationTime);
	swipe->setWidth(width); swipe->setHeight(height);
	m_swipes.push_back(swipe);

	settings.type = EASE_OUT;
	swipe->setScale(glm::vec3(0, 0, 0));
	AppManager::getInstance().getVisualEffectsManager().createScaleEffect(swipe, glm::vec3(0.5, 0.5, 1), glm::vec3(2.0, 2.0, 1), settings);


}

void SwipeScene::startSwipeRectangle(EffectSettings& settings)
{
	float width = AppManager::getInstance().getSettingsManager().getAppWidth();
	float height = AppManager::getInstance().getSettingsManager().getAppHeight();

	string resourceName = "RectSwipe";

	glm::vec3 pos(0, 0, 0);
	shared_ptr<SwipeVisual> swipe = make_shared<SwipeVisual>(pos, resourceName, settings.animationTime);
	swipe->setWidth(width); swipe->setHeight(height);
	m_swipes.push_back(swipe);

	//settings.animationTime *= 0.5f;
	settings.type = EASE_OUT;
	swipe->setPosition(ofPoint(-width, 0));
	AppManager::getInstance().getVisualEffectsManager().createMoveEffect(swipe, glm::vec3(-width * 0.5, height*0.5, 0), glm::vec3(width*0.5 + width, height*0.5, 0), settings);

}


void SwipeScene::willFadeIn()
{
    ofLogNotice("SwipeScene::willFadeIn");
    AppManager::getInstance().getGuiManager().setColorCorrectionType(2);
	AppManager::getInstance().getGuiManager().loadPresets(this->getName());
}

void SwipeScene::willDraw(){
    ofLogNotice("SwipeScene::willDraw");
}

void SwipeScene::willFadeOut() {
    ofLogNotice("SwipeScene::willFadeOut");
	AppManager::getInstance().getGuiManager().savePresets(this->getName());
}

void SwipeScene::willExit() {
    this->deleteSwipes();
    ofLogNotice("SwipeScene::willExit");
}


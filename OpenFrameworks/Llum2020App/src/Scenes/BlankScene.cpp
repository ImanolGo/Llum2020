/*
 *  BlankScene.cpp
 *  Llum 2020 App
 *
 *  Created by Imanol Gomez on 01/02/20.
 *
 */


#include "BlankScene.h"
#include "AppManager.h"


BlankScene::BlankScene(): ofxScene("Blank"){}

void BlankScene::setup() {
    ofLogNotice("BlankScene::setup");
}

void BlankScene::update() {
    
}

void BlankScene::draw() {

	float width = AppManager::getInstance().getSettingsManager().getAppWidth();
	float height = AppManager::getInstance().getSettingsManager().getAppHeight();
	ofClear(0);
	ofSetColor(0);
	ofDrawRectangle(0, 0, width, height);
}

void BlankScene::willFadeIn() {
	 AppManager::getInstance().getGuiManager().loadPresets(this->getName());
     ofLogNotice("BlankScene::willFadeIn");
}

void BlankScene::willDraw() {
    ofLogNotice("BlankScene::willDraw");
}

void BlankScene::willFadeOut() {
	AppManager::getInstance().getGuiManager().savePresets(this->getName());
    ofLogNotice("BlankScene::willFadeOut");
}

void BlankScene::willExit() {
    ofLogNotice("BlankScene::willExit");
}

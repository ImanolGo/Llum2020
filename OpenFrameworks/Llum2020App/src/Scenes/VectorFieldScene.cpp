/*
 *  VectorFieldScene.cpp
 *  Llum 2020 App
 *
 *  Created by Imanol Gomez on 05/02/20.
 *
 */



#include "AppManager.h"
#include "VectorFieldScene.h"

VectorFieldScene::VectorFieldScene(string name) : ofxScene(name), m_targetAddedSpeed(0.0), m_addedSpeed(0.0)
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


void VectorFieldScene::update()
{

	this->updateSpeed();
	this->updateVectorField();
	this->updateFbo();

}
void VectorFieldScene::updateSpeed()
{
	bool isOnset = AppManager::getInstance().getAudioManager().getLowOnset();
	auto parameters = AppManager::getInstance().getParticlesManager().getParameters();
	if (isOnset) {
		m_addedSpeed = parameters.speed * 2.0;
	}

	m_addedSpeed = m_addedSpeed + (m_targetAddedSpeed - m_addedSpeed)*0.08f;

}


void VectorFieldScene::updateVectorField()
{
	auto parameters = AppManager::getInstance().getParticlesManager().getParameters();
	parameters.speed += m_addedSpeed;

	float angleRadiands = degree2radian(parameters.direction);

	glm::vec3 force;
	force.x = -parameters.directionMag*sin(angleRadiands);
	force.y = parameters.directionMag*cos(angleRadiands);
	m_vectorField.addForce(force);

	m_vectorField.addParameters(parameters);
	m_vectorField.update();

	//ofLogNotice() << " speed = " << parameters.speed;
}

void VectorFieldScene::setColors()
{
	
	int numParticles = m_vectorField.getNumParticles();
	auto& texture = AppManager::getInstance().getColorManager().getFboGradient().getTexture();
	ofPixels pix;
	texture.readToPixels(pix); // now all the pixels from tex are in pix'
	int y = texture.getHeight() / 2;

	for (int i = 0; i < numParticles; i++) {
		int x = (int)ceil(ofRandom(texture.getWidth()));
		m_vectorField.setColor(i, pix.getColor(x, y));
	}
}

void VectorFieldScene::updateFbo()
{
	m_fbo.begin();
	ofClear(0, 255);
	this->drawVectorField();
	m_fbo.end();
}

void VectorFieldScene::draw()
{
	ofClear(0);
	//ofBackground(color);
	AppManager::getInstance().getColorManager().beginColorCorrection();
	m_fbo.draw(0, 0);
	AppManager::getInstance().getColorManager().endColorCorrection();
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
	this->setColors();
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

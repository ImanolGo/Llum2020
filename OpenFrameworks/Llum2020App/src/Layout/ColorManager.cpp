/*
 *  ColorManager.cpp
 *  Llum 2020 App
 *
 *  Created by Imanol Gomez on 01/02/20.
 *
 */




#include "ofMain.h"

#include "ColorManager.h"


const string ColorManager::GRADIENTS_PATH = "images/gradients/";

ColorManager::ColorManager(): Manager(), m_useHueCorrection(false)
{
	//Intentionally left empty
}


ColorManager::~ColorManager()
{
    ofLogNotice() <<"ColorManager::Destructor";
}


void ColorManager::setup()
{
	if(m_initialized)
		return;

    ofLogNotice() <<"ColorManager::initialized";
	
	this->setupGradients();


	Manager::setup();
	
  
}

void ColorManager::update()
{

}


void ColorManager::draw()
{
	m_mainGradient.draw(300, 300);
}

void ColorManager::setupGradients()
{
	m_mainGradient.allocate(100, 100, OF_IMAGE_COLOR);

	ofDirectory dir(GRADIENTS_PATH);
	if (!dir.exists()) {
		ofLogNotice() << "ColorManager::setupGradients -> Folder not found: " << GRADIENTS_PATH;
		return;
	}

	//only show image files
	dir.allowExt("png");
	dir.allowExt("jpg");
	dir.allowExt("jpeg");

	if( dir.listDir() == 0){
	    ofLogNotice() <<"ColorManager::setupGradients -> No image files found in: " << GRADIENTS_PATH;
	    return;
	}

	dir.sort();


	for (int i = 0; i < dir.size(); i++)
	{
		ofImage image;

		if (image.load(dir.getPath(i))) {
			pair<string, ofImage> gradient(dir.getName(i), image);
			m_gradients.push_back(gradient);
			ofLogNotice() << "ColorManager::setupGradients -> Loaded image " << dir.getName(i);
		}
	}

	if (!m_gradients.empty()) {
		m_mainGradient = m_gradients.front().second;
	}

}


void ColorManager::changeGradientIndex(int& index)
{
	if (index < 0 || index >= m_gradients.size()) {
		return;
	}

	ofLogNotice() << "ColorManager::changeGradientIndex << scene index " << index;

	m_mainGradient = m_gradients[index].second;

}



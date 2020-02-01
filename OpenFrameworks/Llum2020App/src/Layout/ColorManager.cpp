/*
 *  ColorManager.cpp
 *  Llum 2020 App
 *
 *  Created by Imanol Gomez on 01/02/20.
 *
 */




#include "ofMain.h"

#include "ColorManager.h"

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

	Manager::setup();
  
}

void ColorManager::update()
{

}


void ColorManager::draw()
{

}



/*
 *  ParticlesManager.cpp
 *  Llum 2020 App
 *
 *  Created by Imanol Gomez on 05/02/20.
 *
 */


#include "ofMain.h"

#include "ParticlesManager.h"
#include "AppManager.h"


ParticlesManager::ParticlesManager(): Manager()
{
	//Intentionally left empty
}


ParticlesManager::~ParticlesManager()
{
    ofLogNotice() <<"ParticlesManager::Destructor" ;
}


void ParticlesManager::setup()
{
	if(m_initialized)
		return;


	Manager::setup();
    
    
    ofLogNotice() <<"ParticlesManager::initialized" ;
    
}


void ParticlesManager::update()
{
 
}





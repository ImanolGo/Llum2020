/*
 *  KeyboardManager.cpp
 *  Llum 2020 App
 *
 *  Created by Imanol Gomez on 01/02/20.
 *
 */


#include "KeyboardManager.h"
#include "AppManager.h"


KeyboardManager::KeyboardManager(): Manager()
{
    //Intentionally left empty
}

KeyboardManager::~KeyboardManager()
{
   ofLogNotice() << "KeyboardManager::destructor";
}


//--------------------------------------------------------------

void KeyboardManager::setup()
{
    if(m_initialized)
        return;
    
    Manager::setup();
    
    ofLogNotice() <<"KeyboardManager::initialized" ;
    this->addListeners();
}

void KeyboardManager::addListeners()
{
    ofRegisterKeyEvents(this); // this will enable the InteractiveVisual class to listen to the key events.
}

void KeyboardManager::keyPressed(ofKeyEventArgs &e)
{
    int key = e.key;
    
    //ofLogVerbose() <<"KeyboardManager::keyPressed-> " + ofToString(key);
    
    if(key == '1'){
        AppManager::getInstance().getLayoutManager().setDrawMode(LayoutManager::DRAW_3D);
    }
    else if(key == '2'){
        AppManager::getInstance().getLayoutManager().setDrawMode(LayoutManager::DRAW_2D);
    }
    else if(key == '3'){
        AppManager::getInstance().getLayoutManager().setDrawMode(LayoutManager::DRAW_SCENE);
    }

	else if (key == 's' || key == 'S') {
		AppManager::getInstance().getGuiManager().toggleShowMode();
	}
   
    
    
}

void KeyboardManager::keyReleased(ofKeyEventArgs &e)
{
    int key = e.key;
    
    //ofLogVerbose() <<"KeyboardManager::keyReleased-> " + ofToString(key);
    
}











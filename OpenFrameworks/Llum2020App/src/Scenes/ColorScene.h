/*
 *  ColorScene.h
 *  Llum 2020 App
 *
 *  Created by Imanol Gomez on 01/02/20.
 *
 */

#pragma once

#include "ofxScene.h"

class ColorScene : public ofxScene {

public:

    //! Constructor
    ColorScene();
    
    //! Destructor
    ~ColorScene();
    
    //! Set up the scene
    void setup();

    //! Update the scene
    void update();

    //! Draw the scene
    void draw();
    
    //! Called when fading in
    void willFadeIn();

    //! Called when to start drawing
    void willDraw();

    //! Called fading out
    void willFadeOut();

    //! Called when exit
    void willExit();
    
private:
    
   
    
private:
    
    
    bool          m_initialized;

};





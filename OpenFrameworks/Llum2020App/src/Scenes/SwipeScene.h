/*
 *  SwipeScene.h
 *  Llum 2020 App
 *
 *  Created by Imanol Gomez on 10/02/20.
 *
 */

#pragma once

#include "ofxScene.h"
#include "ImageVisual.h"
#include "AppManager.h"




class SwipeVisual : public ImageVisual {

public:

	//! Constructor
	SwipeVisual(const ofVec3f& pos, const string& resourceName, float lifetim);

	//! Destructor
	~SwipeVisual();

	//! Draws the visual
	virtual void update();

	bool    isAlive() { return m_isAlive; }

	void   setLifetime(float lifetime);

private:

	bool     m_isAlive;          ///< defines if the visual visual is alive or not
	float    m_timeLeft;         ///< defines the time left for a visual in seconds

};

class SwipeScene : public ofxScene {
    
public:
    
    //! Constructor
    SwipeScene();
    
    //! Destructor
    ~SwipeScene();
    
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
    
	void updateTrigger();

	void updateSwipes();

    void drawSwipes();
    
    void deleteSwipes();
    
    void startSwipe();

	void startSwipeRing(EffectSettings& settings);

	void startSwipeRectangle(EffectSettings& settings);
    
private:
    
	typedef vector < shared_ptr<SwipeVisual> > SwipesVector;  ///< Defines a vector of visuals

	SwipesVector					m_swipes;
    
};

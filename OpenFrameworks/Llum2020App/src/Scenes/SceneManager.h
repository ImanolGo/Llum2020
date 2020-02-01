/*
 *  SceneManager.h
 *  Llum 2020 App
 *
 *  Created by Imanol Gomez on 01/02/20.
 *
 */

#pragma once

#include "Manager.h"
#include "ofxSceneManager.h"
#include "ofxSimpleTimer.h"
#include "ofxFastFboReader.h"


//========================== class SceneManager ==============================
//============================================================================
/** \class SceneManager SceneManager.h
 *	\brief Class managing the scenes of the application
 *	\details It creates and manages all the scenes 
 */


class SceneManager: public Manager
{
    
public:

    //! Constructor
    SceneManager();

    //! Destructor
    ~SceneManager();

    //! Set-up the scenes
    void setup();
    
    //! Update the scenes
    void update();
    
    //! Draw the sceneManager
    void draw();
    
    //! Draw the sceneManager within a window rectangle
    void draw(const ofRectangle& rect);
    
    //! Changes the scene according to a name
    void changeScene(string sceneName);
    
    //! Changes the scene according to a index
    void changeSceneIndex(int& sceneIndex);
    
    //! changes transition time
    void onTransitionTimeChange(float& value);
    
    //! Returns the number of total secenes
    int getNumberScenes();
    
    //! Returns the name of a scene given the index
    string getSceneName(int sceneIndex);
    
    //! Returns the index a scene given a name. It returns -1 if it doesn't find any
    int getIndex(string& sceneName);
    
    const ofFbo& getFbo() {return m_fbo;}
    
    void sceneTimerCompleteHandler( int &args ) ;
    
    void onChangeSceneDuration(float& value);
    
    const string& getCurrentSceneName() const {return m_currentSceneName;}
 

    void addVideos();
    
    void setVideoIndex(int value);
    
    int getSceneOffset() const {return m_sceneOffset;}
    
    int getCurrentVideoIndex() const {return m_currentVideoIndex;}
    
    bool getCurrentStatus() const {return m_status;}
    
    
private:
    
    //! Create the scenes
    void createScenes();
    
    //! Set up the fbo that saves the texture.
    void setupFbo();
    
    //! Set up the scene timer
    void setupTimer();
    
    //! Update the scene timer
    void updateTimer();
    
    //! updates all the scenes
    void updateScenes();
    
    //! updates the fbo
    void updateFbo();

    //! updates the fbo
    void updatePixels();
    
    void sendSceneChange();
    
    void removeVideos();
    
    void removeScenes();
    
private:

    shared_ptr<ofxSceneManager>          m_mySceneManager;
    ofFbo                    m_fbo, m_fboColor;
    ofxSimpleTimer           m_sceneTimer;
    float                    m_alpha;
    ofxFastFboReader         m_reader;
    ofParameterGroup         m_parameters;
    
    vector<string>           m_sceneList;
    string                   m_currentSceneName;
    float                    m_transitionTime;
    int                      m_sceneOffset;
    bool                     m_status;
    int                      m_currentVideoIndex;
  
};

//==========================================================================



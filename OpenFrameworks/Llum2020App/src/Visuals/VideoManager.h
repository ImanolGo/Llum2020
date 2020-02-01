/*
 *  VideoManager.h
 *  Kontrast Mooment Dress App
 *
 *  Created by Imanol Gomez on 20/01/20.
 *
 */

#pragma once

#include "Manager.h"
#include "SettingsManager.h"
#include "ofxBlur.h"
#include "ofxFastFboReader.h"

//========================== class VideoManager ==============================
//============================================================================
/** \class VideoManager VideoManager.h
 *	\brief Class managing the video player visuals
 *	\details it creates and updates the video player
 */


class VideoManager: public Manager
{
    
    static const string VIDEO_PATH;
    
public:
    
    //! Constructor
    VideoManager();
    
    //! Destructor
    ~VideoManager();
    
    //! Setup the Video Manager
    void setup();
    
    //! Update the Video Manager
    void update();
    
    //! Draw the Video Manager
    void draw();
    
    //! Draw the Video Manager
    void draw(float width, float height);
    
    void loadVideos(string& path);
    
    void load(string& name);
   
    
    void setBlurScale(float& value);
    
    void setSpeed(float& value);
    
    void next();
    
    void setVideoIndex(int i);
    
    void play();
    
    void stop();
    
    void pause();
    
    void reload();
    
    int getCurrentIndex() const {return m_currentVideoIndex;}
    
    int getCurrentStatus() const {return m_status;}
    
    const ResourcesPathMap& getVideoResourcesPath() const {return m_videoResourcesPath;}
    
    const vector<string>& getVideoNames() const {return m_videoNames;}


private:
    
    void setupFbo();
    
    void setupShaders(float width,float height);
    
    void setupBlur(float width, float height);
    
    void updateFbos();
    
    void updateVideo();
    
    void drawFbo();
    
    void drawVideo();
    
    bool isVideo(string& name);
    
private:
    
    
    vector<string>      m_videoNames;
    
    ResourcesPathMap    m_videoResourcesPath;   ///< stores the video paths

    ofVideoPlayer 	    m_videoPlayer;
    ofxBlur             m_blur;
    ofxFastFboReader    m_reader;
  
    ofFbo           m_fbo;
    ofFbo           m_exportFbo;
    
    ofColor         m_color;
    int             m_frameNumber;
    int             m_currentVideoIndex;
    float           m_blurScale;
    bool            m_status;
    bool            m_playing;

};





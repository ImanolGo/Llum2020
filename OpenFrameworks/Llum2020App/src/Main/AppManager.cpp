/*
 *  AppManager.cpp
 *  Llum 2020 App
 *
 *  Created by Imanol Gomez on 01/02/20.
 *
 */

#include "ofMain.h"

#include "AppManager.h"

AppManager& AppManager::getInstance()
{
	// The only instance
	// Guaranteed to be lazy initialized
	// Guaranteed that it will be destroyed correctly
	static AppManager    m_instance;
    return m_instance;

}

AppManager::AppManager(): Manager(), m_debugMode(false), m_initialized(false)
{
   //Intentionally left empty
}


AppManager::~AppManager()
{
    ofLogNotice() <<"AppManager::Destructor";
}


void AppManager::setup()
{
	if(m_initialized)
		return;
    
    

	Manager::setup();
    
    this->setupOF();
	this->setupManagers();

    
    m_initialized = true;
    ofLogNotice() << "AppManager::initialized";
    
}

void AppManager::setupOF()
{
    ofSetLogLevel(OF_LOG_NOTICE);
    ofSetVerticalSync(false);
    ofSetFrameRate(60);
	//ofDisableArbTex();
    
    
    //ofSetEscapeQuitsApp(false);
    //ofSetDataPathRoot("./data/");
    //ofSetDataPathRoot(ofFilePath::getCurrentExeDir() + "./data");
    
    ofSetBackgroundAuto(true);
    
    bool isOFDataFolderBundled = false;
    if( ofFile::doesFileExist("../Resources/data", false) ){
        isOFDataFolderBundled = true;
    }
    if( isOFDataFolderBundled ){
        ofSetDataPathRoot(ofFilePath::getCurrentExeDir() + "/../Resources/data/"); // > = of0.10.0
        //ofSetDataPathRoot("../Resources/data/"); // < = of0.9.8
    }
    
    //ofLogNotice() << "AppManager::setupOF -> "<< ofFilePath::getCurrentExeDir() ;
    ofLogNotice() << "AppManager::setupOF -> OF data path is:  "<< ofToDataPath("",true);
    //ofLogNotice() << " OF data path is " << ofFilePath::getAbsolutePath( ofToDataPath("") ) << endl;
    //ofSetDataPathRoot("../Resources/data/");
    //ofSetDataPathRoot(ofFilePath::getCurrentExeDir() + "/../Resources/data");
    
    
#ifdef TARGET_LINUX
    ofAppGLFWWindow* win;
    win = dynamic_cast<ofAppGLFWWindow *> (ofGetWindowPtr());
    win->setWindowIcon("images/icons/icon.png");
#endif
    
}


void AppManager::setupManagers()
{
    m_settingsManager.setup();
    m_resourceManager.setup();
    //m_viewManager.setup();
	m_audioManager.setup();
    m_visualEffectsManager.setup();
	m_oscManager.setup();
	m_midiManager.setup();
    m_layoutManager.setup();
    m_videoManager.setup();
    m_ledsManager.setup();
    m_modelManager.setup();
    m_keyboardManager.setup();
	m_colorManager.setup();
	m_particlesManager.setup();
    m_sceneManager.setup();
  
    m_guiManager.setup();
    m_guiManager.onSceneChange("NoiseShader");
}

void AppManager::update()
{
    if(!m_initialized)
        return;
    
    
    m_visualEffectsManager.update();
	m_oscManager.update();
	m_guiManager.update();
    //m_viewManager.update();
   // m_videoManager.update();
	m_audioManager.update();
	m_particlesManager.update();
    m_sceneManager.update();
    m_ledsManager.update();
    m_modelManager.update();
    m_layoutManager.update();
   
}


void AppManager::draw()
{
    
    if(!m_initialized)
        return;
    
    ofBackground(17,17,17);
    m_layoutManager.draw();
	//m_sceneManager.draw();
    m_guiManager.draw();  
	//m_audioManager.draw();
	//ofDisableArbTex();
}	

void AppManager::toggleDebugMode()
{
    m_debugMode = !m_debugMode;
    setDebugMode(m_debugMode);
}


void AppManager::setDebugMode(bool showDebug)
{
    m_debugMode = showDebug;
    
    ofLogNotice()<<"AppManager::setDebugMode-> " << m_debugMode;
    
    if(m_debugMode){
        //ofSetLogLevel(OF_LOG_VERBOSE);
    }
    else{
        ofSetLogLevel(OF_LOG_NOTICE);
    }
    

    m_guiManager.showGui(m_debugMode);
    
}

void AppManager::changeFrameRate(int& fps)
{
    ofSetFrameRate(fps);
}





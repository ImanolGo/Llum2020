/*
 *  SceneManager.cpp
 *  Llum 2020 App
 *
 *  Created by Imanol Gomez on 01/02/20.
 *
 */

#include "ofMain.h"

#include "SceneManager.h"
#include "scenes.h"
#include "AppManager.h"

SceneManager::SceneManager(): Manager(), m_alpha(-1), m_transitionTime(0.5), m_sceneOffset(2), m_currentVideoIndex(0), m_status(false), m_showMode(false)
{
	//Intentionally left empty
}


SceneManager::~SceneManager()
{
    ofLogNotice() <<"SceneManager::Destructor";
}


void SceneManager::setup()
{
	if(m_initialized)
		return;

	Manager::setup();

    this->createScenes();
    this->setupFbos();
    ofLogNotice() <<"SceneManager::initialized";

}


void SceneManager::createScenes()
{
    m_mySceneManager = make_shared<ofxSceneManager>();

    m_mySceneManager->setTransitionFade();
	//m_mySceneManager->setTransitionDissolve();
    
    shared_ptr<ofxScene> scene;
    
     m_sceneOffset = 0;
    
    //Create Blank Scene
    scene = shared_ptr<ofxScene> (new BlankScene());
    m_mySceneManager->addScene(scene);
    m_sceneOffset++;
    
    //Create Color Scene
    auto colorScene = shared_ptr<ColorScene> (new ColorScene());
    colorScene->setup();
    m_mySceneManager->addScene(colorScene);
    m_sceneOffset++;
    
    //Create Test Scene
    auto sceneTest = shared_ptr<TestScene> (new TestScene());
    sceneTest->setup();
    m_mySceneManager->addScene(sceneTest);
    m_sceneOffset++;
    
    
    //Create shader Scene
    auto shaderScene = shared_ptr<ShaderScene> (new ShaderScene("NoiseShader"));
    shaderScene->setup();
    m_mySceneManager->addScene(shaderScene);
    m_sceneOffset++;

    //Create shader Scene
    shaderScene = shared_ptr<ShaderScene> (new ShaderScene("CirclesShader"));
    shaderScene->setup();
    m_mySceneManager->addScene(shaderScene);
    m_sceneOffset++;

    //Create shader Scene
    shaderScene = shared_ptr<ShaderScene> (new ShaderScene("SparklesShader"));
    shaderScene->setup();
    m_mySceneManager->addScene(shaderScene);
    m_sceneOffset++;

    //Create shader Scene
    shaderScene = shared_ptr<ShaderScene> (new ShaderScene("BreathShader"));
    shaderScene->setup();
    m_mySceneManager->addScene(shaderScene);
    m_sceneOffset++;

    //Create shader Scene
    shaderScene = shared_ptr<ShaderScene> (new ShaderScene("CloudsShader"));
    shaderScene->setup();
    m_mySceneManager->addScene(shaderScene);
    m_sceneOffset++;

	//Create shader Scene
	shaderScene = shared_ptr<ShaderScene>(new ShaderScene("SunsetShader"));
	shaderScene->setup();
	m_mySceneManager->addScene(shaderScene);
	m_sceneOffset++;

	//Create shader Scene
	shaderScene = shared_ptr<ShaderScene>(new ShaderScene("StarWavesShader"));
	shaderScene->setup();
	m_mySceneManager->addScene(shaderScene);
	m_sceneOffset++;

	//Create shader Scene
	shaderScene = shared_ptr<ShaderScene>(new ShaderScene("CircularPlasmaShader"));
	shaderScene->setup();
	m_mySceneManager->addScene(shaderScene);
	m_sceneOffset++;

	//Create swipe Scene
	scene = shared_ptr<SwipeScene>(new SwipeScene());
	m_mySceneManager->addScene(scene);
	m_sceneOffset++;

	//Create Etsatic Scene
	scene = shared_ptr<ofxScene>(new VectorFieldScene("Ecstatic"));
	m_mySceneManager->addScene(scene);

	//Create Melancholic
	auto vectorScene = shared_ptr<VectorFieldScene>(new VectorFieldScene("Melancholic"));
	vectorScene->setAdditiveBlend(true);
	m_mySceneManager->addScene(vectorScene);

    
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height = AppManager::getInstance().getSettingsManager().getAppHeight();
	this->onTransitionTimeChange(m_transitionTime);
    
    m_mySceneManager->run(width, height);
    
    
    ofLogNotice() <<"SceneManager::createScenes-> w = " << width << ", h = " << height;
    ofLogNotice() <<"SceneManager::createScenes-> transition time = " << m_transitionTime << "s";


}


void SceneManager::setupFbos()
{
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height = AppManager::getInstance().getSettingsManager().getAppHeight();
    

	ofLogNotice() << "SceneManager::setupFbos << width =  " << width << ", height = " << height;

    //float width = ofGetWidth();
    //float height = ofGetHeight();

    m_fbo.allocate(width, height, GL_RGB);
    m_fbo.begin(); ofClear(0); m_fbo.end();
    
    m_fboColor.allocate(width, height, GL_RGB);
    m_fboColor.begin(); ofClear(0, 255); m_fboColor.end();

	m_fboScene.allocate(width, height, GL_RGB);
	m_fboScene.begin(); ofClear(0); m_fboScene.end();
     
}


void SceneManager::setupTimer()
{
	auto time = AppManager::getInstance().getSettingsManager().getSceneTimer();
	m_sceneTimer.setup(time * 1000);
	m_sceneTimer.start(false);
	ofAddListener(m_sceneTimer.TIMER_COMPLETE, this, &SceneManager::sceneTimerCompleteHandler);

	ofLogNotice() << "SceneManager::setupTimer << Time = : " << time << "s";
}


void SceneManager::update()
{
    this->updateScenes();
    this->updateFbo();
    this->updatePixels();
    this->updateTimer();
}

void SceneManager::updateFbo()
{

	ofEnableAlphaBlending();

	m_fboScene.begin();
		AppManager::getInstance().getColorManager().beginBlur();
		m_mySceneManager->draw();
		AppManager::getInstance().getColorManager().endBlur();
	m_fboScene.end();


	//m_fboColor.begin();
 //       ofClear(0);
	//	AppManager::getInstance().getColorManager().beginColorCorrection();
	//	 m_fboScene.draw(0,0);
	//	AppManager::getInstance().getColorManager().endColorCorrection();
	//m_fboColor.end();
    
    
    m_fbo.begin();
		ofClear(0);
		AppManager::getInstance().getColorManager().beginColorLevels();
		m_fboScene.draw(0,0);
		AppManager::getInstance().getColorManager().endColorLevels();
    m_fbo.end();
}


void SceneManager::updatePixels()
{
	if (m_showMode) {
		return;
	}

    ofPixels pixels;
    m_reader.readToPixels(m_fbo, pixels, OF_IMAGE_COLOR_ALPHA);
    //m_fbo.readToPixels(pixels);
    AppManager::getInstance().getLedsManager().setPixels(pixels);
}


void SceneManager::updateScenes()
{
    m_mySceneManager->update();
}

void SceneManager::updateTimer()
{
    m_sceneTimer.update();
}


void SceneManager::draw()
{
    string name = "Scene";
    ofRectangle frame;
    auto rect = AppManager::getInstance().getLayoutManager().getWindowRect(name);
    float ratio = m_fbo.getWidth()/ m_fbo.getHeight();
    frame.height = rect->getHeight();
    frame.width = frame.height*ratio;
    
    if( frame.width > rect->getWidth() ){
        frame.width = rect->getWidth();
        frame.height = frame.width/ratio;
    }
    
    frame.x = rect->getWidth()*0.5 - frame.width*0.5;
    frame.y = rect->getHeight()*0.5 - frame.height*0.5;
    
    m_fbo.draw(frame);
}


void SceneManager::draw(const ofRectangle& rect)
{
    m_fbo.draw(rect.x,rect.y,rect.width,rect.height);
}


void SceneManager::removeVideos()
{
    ofLogNotice() <<"SceneManager::removeVideos";

    int index = 0;
    //this->changeSceneIndex(index);
    //AppManager::getInstance().getGuiManager().onSceneChange(0);
    //changeSceneIndex
    
    auto& videoPaths = AppManager::getInstance().getVideoManager().getVideoResourcesPath();
    auto scenes = m_mySceneManager->scenes;

    for(int i=m_sceneOffset ; i < scenes.size(); i++){
        ofLogNotice() <<"SceneManager::remove video -> " << scenes[i]->getName();
        m_mySceneManager->removeScene(scenes[i]);
    }
}


void SceneManager::removeScenes()
{
    ofLogNotice() <<"SceneManager::removeScenes";
    
    int index = 0;
    //this->changeSceneIndex(index);
    //AppManager::getInstance().getGuiManager().onSceneChange(0);
    //changeSceneIndex
    
    auto& videoPaths = AppManager::getInstance().getVideoManager().getVideoResourcesPath();
    auto scenes = m_mySceneManager->scenes;
    
    for(int i=0 ; i < scenes.size(); i++){
        ofLogNotice() <<"SceneManager::remove video -> " << scenes[i]->getName();
        m_mySceneManager->removeScene(scenes[i]);
    }
}


void SceneManager::addVideos()
{
     
    //this->removeVideos();
    this->removeScenes();
    this->createScenes();
    
    auto& videoPaths = AppManager::getInstance().getVideoManager().getVideoNames();
  
    for(auto& path : videoPaths){
        auto videoScene = shared_ptr<VideoScene>(new VideoScene(path));
        videoScene->setup();
        ofLogNotice() <<"SceneManager::add video scene -> " << path;
        m_mySceneManager->addScene(videoScene);
    }
    
    AppManager::getInstance().getGuiManager().setupScenesGui();
}



void SceneManager::changeScene(string sceneName)
{
    for(auto scene: m_mySceneManager->scenes){
        if(scene->getName() == sceneName){
            ofLogNotice() <<"SceneManager::changeScene -> " << sceneName;
            m_mySceneManager->changeScene(sceneName);
            m_sceneTimer.start(false,true);
            m_currentSceneName = sceneName;
            //this->sendSceneChange();
            
            break;
        }
    }
}

void SceneManager::setVideoIndex(int value)
{
    int size = m_mySceneManager->scenes.size() - m_sceneOffset;
    if(value >= 0  &&  value<size){
        m_currentVideoIndex = value;
    }
}

void SceneManager::changeSceneIndex(int& sceneIndex)
{
    if(sceneIndex < 0 || sceneIndex >= m_mySceneManager->scenes.size()){
        return;
    }
    
    ofLogNotice() <<"SceneManager::changeSceneIndex << scene index " << sceneIndex;

     m_mySceneManager->changeScene(sceneIndex);
     m_sceneTimer.start(false,true);
     m_currentSceneName = this->getSceneName(sceneIndex);
    
     ofLogNotice() <<"SceneManager::changeSceneIndex << scene name " << m_currentSceneName;
    
    
    if(sceneIndex < m_sceneOffset){
        m_status = false;
    }
    else{
         m_status = true;
        m_currentVideoIndex = sceneIndex - m_sceneOffset;
    }
}


void SceneManager::onTransitionTimeChange(float& value)
{
   m_transitionTime = value;
   m_mySceneManager->setSceneDuration(m_transitionTime,m_transitionTime);
   m_sceneTimer.start(false,true);
    
}

string SceneManager::getSceneName(int sceneIndex)
{
    string name = "";
    if(sceneIndex < 0 || sceneIndex >= m_mySceneManager->scenes.size()){
        return name;
    }
    
    return m_mySceneManager->scenes[sceneIndex]->getName();
   
}

int SceneManager::getIndex(string& sceneName)
{
    for(int i = 0; i< m_mySceneManager->scenes.size(); i++){
        if(m_mySceneManager->scenes[i]->getName() == sceneName){
            return i;
        }
    }
    
    return -1;
}

void SceneManager::sceneTimerCompleteHandler( int &args )
{
	this->nextScene();

}

void SceneManager::nextScene()
{
	m_sceneTimer.start(false);

	if (m_sceneList.empty()) {
		this->initializeSceneList();
	}

	string sceneName = m_sceneList.back();  m_sceneList.pop_back();
	AppManager::getInstance().getGuiManager().onSceneChange(sceneName);

	ofLogNotice() << "SceneManager::nextScene << Change Scene: " << sceneName;
}

void SceneManager::sendSceneChange()
{
    
    string address = "preset" + m_currentSceneName;
    
    ofLogNotice() <<"SceneManager::sendSceneChange << OSC Message Scene: " << address;
    
   // AppManager::getInstance().getOscManager().sendIntMessage(1, address);
  
}

void SceneManager::onChangeSceneDuration(float& value)
{
	m_sceneTimer.setup(value * 1000);
	ofLogNotice() << "SceneManager::setupTimer << Time = : " << time << "s";
}

void SceneManager::stopScenes()
{
	m_sceneTimer.stop();
	ofLogNotice() << "SceneManager::nextScene << Stop Scenes!";
}


int SceneManager::getNumberScenes(){
    
    if(m_mySceneManager){
        return m_mySceneManager->scenes.size();
    }
    return 0;
}

void SceneManager::initializeSceneList()
{
	m_sceneList.clear();
	m_sceneList = { "Noise","Ecstatic"};
}

void SceneManager::onShowModeChange(bool& value)
{
	m_showMode = value;
	if (m_showMode == true) {
		AppManager::getInstance().getLayoutManager().setDrawMode(LayoutManager::DRAW_SCENE);
	}
	else {
		AppManager::getInstance().getLayoutManager().setDrawMode(LayoutManager::DRAW_3D);
	}

}
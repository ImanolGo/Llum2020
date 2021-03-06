/*
 *  TestScene.cpp
 *  Llum 2020 App
 *
 *  Created by Imanol Gomez on 01/02/20.
 *
 */


#include "TestScene.h"
#include "AppManager.h"

TestScene::TestScene(): ofxScene("Test"), m_initialized(false), m_totalTime(100), m_speed(-1.0)
{
    //Intentionally left empty
}

TestScene::~TestScene()
{
   //Intentionally left empty
}


void TestScene::setup() {
    
    if(m_initialized){
        return;
    }
    
    ofLogNotice("TestScene::::setup");
    this->setupTimer();
    this->setupRectangles();
    
    m_initialized = true;
    
}

void TestScene::setupTimer()
{
    m_timer.setup( m_totalTime * 1000);
    m_timer.start( false ) ;
    ofAddListener( m_timer.TIMER_COMPLETE , this, &TestScene::sceneTimerCompleteHandler ) ;
    
    ofLogNotice() <<"TestScene::setupTimer << Time = : " << time << "s";
}



void TestScene::setupRectangles()
{
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height = AppManager::getInstance().getSettingsManager().getAppHeight();
    auto pos = glm::vec3(0);
    auto rectangle = make_shared<RectangleVisual>(pos,width,height,false);
    rectangle->setColor(ofColor(255,0,0));
    m_rectangles["Red"] = rectangle;
    
    rectangle = make_shared<RectangleVisual>(pos,width,height,false);
    rectangle->setColor(ofColor(0,255,0));
    m_rectangles["Green"] = rectangle;
    
    rectangle = make_shared<RectangleVisual>(pos,width,height,false);
    rectangle->setColor(ofColor(255,255,255));
    m_rectangles["White"] = rectangle;
    
    pos = glm::vec3(width*0.5, height*0.5,0.0);
    rectangle = make_shared<RectangleVisual>(pos,width,height,true);
    rectangle->setColor(ofColor(0,0,255));
    m_rectangles["Blue"] = rectangle;
    
}


void TestScene::update()
{
    this->updateTimer();
    this->checkTiming();
    
}


void TestScene::updateTimer()
{
    m_timer.update();
}

void TestScene::draw()
{
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height = AppManager::getInstance().getSettingsManager().getAppHeight();

    ofClear(0);
	ofSetColor(0);
	ofDrawRectangle(0, 0, width, height);
    this->drawRectangles();
}

void TestScene::drawRectangles()
{
    for(auto rectangle: m_rectangles){
        rectangle.second->draw();
    }
}


void TestScene::sceneTimerCompleteHandler( int &args )
{
     ofLogNotice() <<"TestScene::setupTimer << sceneTimerCompleteHandler";
    m_timer.start(false,true);
    this->deleteAnimations();
    this->startAnimations();
}

void TestScene::deleteAnimations()
{
    for(auto rectangle: m_rectangles){
        AppManager::getInstance().getVisualEffectsManager().removeAllVisualEffects(rectangle.second);
    }
}

void TestScene::startAnimations()
{
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height = AppManager::getInstance().getSettingsManager().getAppHeight();
    
    EffectSettings settings;
    settings.function = LINEAR;
    settings.startAnimation = 0.0;
    settings.animationTime = m_totalTime/(2*m_rectangles.size());
    
    settings.type = EASE_OUT;
    m_rectangles["Red"]->setPosition(glm::vec3(-width,0, 0));
    AppManager::getInstance().getVisualEffectsManager().createMoveEffect(m_rectangles["Red"], glm::vec3(-width,0, 0), glm::vec3(0,0, 0), settings);
    
    settings.type = EASE_IN;
    settings.startAnimation += settings.animationTime;
    AppManager::getInstance().getVisualEffectsManager().createMoveEffect(m_rectangles["Red"], glm::vec3(0,0,0) , glm::vec3(width,0, 0), settings);
    
    settings.type = EASE_OUT;
    settings.startAnimation += settings.animationTime;
    m_rectangles["Green"]->setPosition(glm::vec3(0,-height,0));
    AppManager::getInstance().getVisualEffectsManager().createMoveEffect(m_rectangles["Green"], glm::vec3(0,-height, 0), glm::vec3(0,0, 0), settings);
    
    settings.type = EASE_IN;
    settings.startAnimation += settings.animationTime;
    AppManager::getInstance().getVisualEffectsManager().createMoveEffect(m_rectangles["Green"], glm::vec3(0,0,0), glm::vec3(0,height, 0), settings);
    
    settings.type = EASE_OUT;
    settings.startAnimation += settings.animationTime;
    m_rectangles["Blue"]->setScale(glm::vec3(0,0,1));
    AppManager::getInstance().getVisualEffectsManager().createScaleEffect(m_rectangles["Blue"], glm::vec3(0,0,1), glm::vec3(1.0,1.0,1.0), settings);
    
    settings.type = EASE_IN;
    settings.startAnimation += settings.animationTime;
    AppManager::getInstance().getVisualEffectsManager().createScaleEffect(m_rectangles["Blue"], glm::vec3(1.0,1.0, 1.0), glm::vec3(0.0,0.0, 1.0), settings);
    
    settings.function = SINUSOIDAL;
    settings.startAnimation += settings.animationTime;
    settings.type = EASE_OUT;
    m_rectangles["White"]->setAlpha(0.0);
    AppManager::getInstance().getVisualEffectsManager().createFadeEffect(m_rectangles["White"], 0.0, 255.0, settings);
    
    settings.startAnimation += settings.animationTime;
    settings.type = EASE_IN;
    AppManager::getInstance().getVisualEffectsManager().createFadeEffect(m_rectangles["White"],255.0, 0.0, settings);
    
}

void TestScene::willFadeIn()
{   ofLogNotice() <<"TestScene::setupTimer << Time = : " << time << "s";
    ofLogNotice("TestScene::willFadeIn");
    this->checkTiming();
    m_timer.start(false,true);
    this->deleteAnimations();
    this->startAnimations();
    AppManager::getInstance().getGuiManager().setColorCorrectionType(0);
	AppManager::getInstance().getGuiManager().loadPresets(this->getName());
}

void TestScene::willDraw(){
    ofLogNotice("TestScene::willDraw");
}

void TestScene::willFadeOut() {
    ofLogNotice("TestScene::willFadeOut");
	AppManager::getInstance().getGuiManager().savePresets(this->getName());
}

void TestScene::willExit() {
    this->deleteAnimations();
    ofLogNotice("TestScene::willExit");
}

void TestScene::checkTiming()
{
    float value = AppManager::getInstance().getGuiManager().getShaderSpeed();
    if (m_speed != value)
    {
        m_speed = value;
        m_totalTime = ofMap(m_speed, 0.0, 2.0, 360, 5.0, true);
        m_timer.setup( m_totalTime * 1000);
        m_timer.start(false,true);
        this->deleteAnimations();
        this->startAnimations();
    }
}



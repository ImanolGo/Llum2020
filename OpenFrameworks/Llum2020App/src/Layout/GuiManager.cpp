/*
 *  GuiManager.cpp
 *  Llum 2020 App
 *
 *  Created by Imanol Gomez on 01/02/20.
 *
 */


#include "ofMain.h"

#include "AppManager.h"

#include "GuiManager.h"
#include "GuiTheme.h"


const string GuiManager::GUI_SETTINGS_FILE_NAME = "xmls/GuiSettings.xml";
const string GuiManager::GUI_SETTINGS_FILE_PATH = "xmls/";

const string GuiManager::GUI_SETTINGS_NAME = "GUI";
const int GuiManager::GUI_WIDTH = 300;


GuiManager::GuiManager(): Manager(), m_showGui(true)
{
    //Intentionally left empty
}


GuiManager::~GuiManager()
{
    this->saveGuiValues();
    ofLogNotice() <<"GuiManager::Destructor";
}


void GuiManager::setup()
{
    if(m_initialized)
        return;
    
    Manager::setup();
    
    
    this->setupGuiParameters();
    this->setupScenesGui();
	this->setupColorsGui();
    this->setupLedsGui();
    this->setupVideoGui();
    this->setupProcessingGroup();
    this->setupShadersGui();
	this->loadGuiValues();
    
    //this->drawGui();

    
    ofLogNotice() <<"GuiManager::initialized";
    
}

void GuiManager::setupGuiParameters()
{
    //create an actual ImGui context before setting up the addon
    ImGui::CreateContext();
    
    //specify a font to use
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF(&ofToDataPath("fonts/roboto/Roboto-Regular.ttf")[0], 16.f);
    
    //ImGui::GetIO().FontGlobalScale = 1.0 / 2.0;
    
    //finally setup the addon ofxImGui::Gui setup;
    m_gui.setup(new GuiTheme());
    ofxImGui::Settings().windowPos  = ofVec2f(0,0);
    ofxImGui::Settings().windowSize = ofVec2f(GUI_WIDTH,ofGetHeight());
    
    m_width = 0;
    m_height = 0;
    
    auto appManager = &AppManager::getInstance();
    
}



void GuiManager::setupScenesGui()
{
     auto scenesManager = &AppManager::getInstance().getSceneManager();
    
    m_sceneNames.clear();
    m_scenesGroup.setName("Scenes");
    m_sceneMode.set("Scene", 0);
    m_sceneMode.addListener(scenesManager, &SceneManager::changeSceneIndex);
    m_scenesGroup.add(m_sceneMode);
    
    for(int i=0; i< scenesManager->getNumberScenes(); i++){
        m_sceneNames.push_back(scenesManager->getSceneName(i));
    }

    m_sceneTransitionTime.set("TransitionTime", 0.5, 0.0, 10);
    m_sceneTransitionTime.addListener(scenesManager, &SceneManager::onTransitionTimeChange);
    m_parameters.add(m_sceneTransitionTime);

}

void GuiManager::setupColorsGui()
{
	auto colorManager = &AppManager::getInstance().getColorManager();
	m_colorsGroup.setName("Colors");

	m_gradientNames.clear();
	auto & gradients = colorManager->getGradients();

	for (int i = 0; i < gradients.size(); i++) {
		m_gradientNames.push_back(gradients[i].first);
	}
	m_gradientMode.set("Gradient", 0);
	m_gradientMode.addListener(colorManager, &ColorManager::changeGradientIndex);
	m_colorsGroup.add(m_gradientMode);



	m_solidColor.set("Color", ofFloatColor::white);
	m_solidColor.addListener(colorManager, &ColorManager::setSolidColor);
	m_presets.add(m_solidColor);


	m_shaderColorNames.clear();
	auto & shader_names = colorManager->getShaderColorNames();

	for (int i = 0; i < shader_names.size(); i++) {
		m_shaderColorNames.push_back(shader_names[i]);
	}
	
	m_shaderColorMode.set("Correction", 0);
	m_shaderColorMode.addListener(colorManager, &ColorManager::changeShaderType);
	m_colorsGroup.add(m_shaderColorMode);

}

void GuiManager::onSceneChange(int sceneIndex)
{
    int size = AppManager::getInstance().getSceneManager().getNumberScenes();
    ofLogNotice() <<"GuiManager::onSceneChange << size -> " << size;

    if(sceneIndex >=0 && sceneIndex < size){
        m_sceneMode = sceneIndex;
        ofLogNotice() <<"GuiManager::onSceneChange << m_sceneMode -> " << m_sceneMode;
    }
}


void GuiManager::onVideoChange(int videoIndex)
{
    int size = AppManager::getInstance().getSceneManager().getNumberScenes();
    int offset = AppManager::getInstance().getSceneManager().getSceneOffset();
    videoIndex+= offset;
    if(videoIndex >=offset && videoIndex < size){
        m_sceneMode = videoIndex;
    }
}

void GuiManager::setupModesGui()
{
    m_modeGroup.setName("View");
    m_viewMode.set("View Mode", 0);
    m_modeGroup.add(m_viewMode);
}


void GuiManager::setupVideoGui()
{
    auto videoManager = &AppManager::getInstance().getVideoManager();
    
    m_videoGroup.setName("Videos");
    m_videoPath.set("VideoPath", " ");
    m_videoPath.addListener(videoManager, &VideoManager::loadVideos);
    m_parameters.add(m_videoPath);
    m_videoGroup.add(m_videoPath);
    
}


void GuiManager::setupShadersGui()
{
    m_shadersGroup.setName("Shaders");
    
    m_shaderSpeed.set("Speed", 1.0, 0.0, 2.0);
	m_presets.add(m_shaderSpeed);
    m_shadersGroup.add(m_shaderSpeed);
    
    m_shaderParameter.set("Parameter", 1.0, 0.0, 5.0);
	m_presets.add(m_shaderParameter);
    m_shadersGroup.add(m_shaderParameter);
    
    m_colorAmount.set("ColorAmount", 0.0, 0.0, 1.0);
	m_presets.add(m_colorAmount);
    m_shadersGroup.add(m_colorAmount);
    
    m_shaderDirection.set("Direction", 0, 0, 3);
	m_presets.add(m_shaderDirection);
    m_shadersGroup.add(m_shaderDirection);
    
}


void GuiManager::setupProcessingGroup()
{
    auto colorManager = &AppManager::getInstance().getColorManager();
    
    m_postProcessingGroup.setName("Post Processing");
    
    m_contrast.set("Contrast", 1.0, 0.0, 2.0);
    m_contrast.addListener(colorManager, &ColorManager::setContrast);
    m_parameters.add(m_contrast);
    m_postProcessingGroup.add(m_contrast);
    
    m_saturation.set("Saturation", 1.0, 0.0, 2.0);
    m_saturation.addListener(colorManager, &ColorManager::setSaturation);
    m_parameters.add(m_saturation);
    m_postProcessingGroup.add(m_saturation);
    
    m_brightness.set("Brightness", 1.0, 0.0, 2.0);
    m_brightness.addListener(colorManager, &ColorManager::setBrightness);
    m_parameters.add(m_brightness);
    m_postProcessingGroup.add(m_brightness);
    
    m_gamma.set("Gamma", 1.0, 0.0, 2.0);
    m_gamma.addListener(colorManager, &ColorManager::setGamma);
    m_parameters.add(m_gamma);
    m_postProcessingGroup.add(m_gamma);
    
    m_minInput.set("MinInput", 0.0, 0.0, 1.0);
    m_minInput.addListener(colorManager, &ColorManager::setMinInput);
    m_parameters.add(m_minInput);
    m_postProcessingGroup.add(m_minInput);
    
    m_maxInput.set("MaxInput", 1.0, 0.0, 1.0);
    m_maxInput.addListener(colorManager, &ColorManager::setMaxInput);
    m_parameters.add(m_maxInput);
    m_postProcessingGroup.add(m_maxInput);
    
    m_minOutput.set("MinOutput", 0.0, 0.0, 1.0);
    m_minOutput.addListener(colorManager, &ColorManager::setMinOutput);
    m_parameters.add(m_minOutput);
    m_postProcessingGroup.add(m_minOutput);
    
    m_maxOutput.set("MaxOutput", 1.0, 0.0, 1.0);
    m_maxOutput.addListener(colorManager, &ColorManager::setMaxOutput);
    m_parameters.add(m_maxOutput);
    m_postProcessingGroup.add(m_maxOutput);
}


void GuiManager::setupLedsGui()
{
    auto ledsManager = &AppManager::getInstance().getLedsManager();
    auto sceneManager = &AppManager::getInstance().getSceneManager();
    
    m_ledsGroup.setName("Leds");
    m_ledsSize.set("Size", 1.0, 0.0, 20.0);
    m_ledsSize.addListener(ledsManager, &LedsManager::setSize);
    m_ledsGroup.add(m_ledsSize);
    m_parameters.add(m_ledsSize);
    
    m_ledsGrid.set("Grid", false);
    m_ledsGrid.addListener(ledsManager, &LedsManager::setGrid);
    m_ledsGroup.add(m_ledsGrid);
    m_parameters.add(m_ledsGrid);
}


void GuiManager::update()
{
    //m_gui.update();
    m_gui.setTheme(new GuiTheme());

}


void GuiManager::draw()
{
    if(!m_showGui)
        return;
    
    this->drawRectangle();
    this->drawGui();
}


void GuiManager::drawGui()
{
    ofEnableAlphaBlending();
 
    m_gui.begin();
       
        auto mainSettings  = ofxImGui::Settings();
        //ofxImGui::Settings().windowPos  = ofVec2f(-LayoutManager::MARGIN,-LayoutManager::MARGIN);
       // ofxImGui::Settings().windowSize = ofVec2f(GUI_WIDTH,ofGetHeight());
        if (ofxImGui::BeginWindow("GUI", mainSettings, false))
        {
    
            ImGui::Text("%.1f FPS (%.3f ms/frame)", ofGetFrameRate(), 1000.0f / ImGui::GetIO().Framerate);
            
           
            if (ofxImGui::BeginTree(m_scenesGroup, mainSettings))
            {
                ofxImGui::AddParameter(m_sceneTransitionTime);
                ofxImGui::AddCombo(m_sceneMode, m_sceneNames);
                ofxImGui::EndTree(mainSettings);
            }

			if (ofxImGui::BeginTree(m_colorsGroup, mainSettings))
			{
				ofxImGui::AddParameter(m_solidColor);
				ofxImGui::AddCombo(m_gradientMode, m_gradientNames);
				ImGui::Image(GetImTextureID(AppManager::getInstance().getColorManager().getGradient()), ImVec2(GUI_WIDTH, 50));
				ofxImGui::AddCombo(m_shaderColorMode, m_shaderColorNames);
				ofxImGui::EndTree(mainSettings);
			}
            
            if (ofxImGui::BeginTree(m_videoGroup, mainSettings))
            {
                ofxImGui::AddParameter(m_videoPath);
                
                if (ImGui::Button("Load Video Folder..."))
                {
                    auto dialogResult = ofSystemLoadDialog("Load Video Folder", true, ofToDataPath(""));
                    if (dialogResult.bSuccess)
                    {
                        m_videoPath = dialogResult.filePath;
                    }
                }
                
                
                ofxImGui::EndTree(mainSettings);
                
            }
            
            if (ofxImGui::BeginTree(m_ledsGroup, mainSettings))
            {
                ofxImGui::AddParameter(m_ledsGrid);
                ofxImGui::AddParameter(m_ledsSize);
                ofxImGui::EndTree(mainSettings);
            }

            
            if (ofxImGui::BeginTree(m_postProcessingGroup, mainSettings))
            {
                //auto & group =
                
                ofxImGui::AddParameter(m_postProcessingGroup.getFloat("Contrast"));
                ofxImGui::AddParameter(m_postProcessingGroup.getFloat("Saturation"));
                ofxImGui::AddParameter(m_postProcessingGroup.getFloat("Brightness"));
                //ofxImGui::AddParameter(m_postProcessingGroup.getFloat("Blur"));
                ofxImGui::AddParameter(m_postProcessingGroup.getFloat("Gamma"));
                ofxImGui::AddParameter(m_postProcessingGroup.getFloat("MinInput"));
                ofxImGui::AddParameter(m_postProcessingGroup.getFloat("MaxInput"));
                ofxImGui::AddParameter(m_postProcessingGroup.getFloat("MinOutput"));
                ofxImGui::AddParameter(m_postProcessingGroup.getFloat("MaxOutput"));
                ofxImGui::EndTree(mainSettings);
            }
            
            if (ofxImGui::BeginTree(m_shadersGroup, mainSettings))
            {
                //auto & group =
                ofxImGui::AddParameter(m_shadersGroup.getFloat("Speed"));
                ofxImGui::AddParameter(m_shadersGroup.getFloat("ColorAmount"));
                ofxImGui::AddParameter(m_shadersGroup.getFloat("Parameter"));
                ofxImGui::AddParameter(m_shadersGroup.getInt("Direction"));
                ofxImGui::EndTree(mainSettings);
            }
            
            
        }
    
        ofxImGui::EndWindow(mainSettings);
    m_gui.end();
    
    ofDisableAlphaBlending();
    
    this->updateSize(mainSettings);
    
   
}

void GuiManager::updateSize(const ofxImGui::Settings& settings)
{
    if(m_width!= settings.windowSize.x){
         m_width = settings.windowSize.x;
         AppManager::getInstance().getLayoutManager().windowResized(ofGetWidth(), ofGetHeight());
    }
   
    m_height = settings.windowSize.y;
    m_position = ofPoint(settings.windowPos.x, settings.windowPos.y);
}



void GuiManager::loadPresets(string path)
{
	if (path.empty()) {
		return;
	}
	
	path = GUI_SETTINGS_FILE_PATH + "Preset_" + path + ".xml";

	ofLogNotice() << "GuiManager::loadPresets-> loading values from: " << path;

	ofXml xml;
	xml.load(path);

	ofDeserialize(xml, m_presets);
}

void GuiManager::savePresets(string path)
{

	if (path.empty()) {
		return;
	}

	path = GUI_SETTINGS_FILE_PATH + "Preset_" + path + ".xml";

    ofLogNotice() <<"GuiManager::savePresets-> saving values from: " << path;
    
    ofXml xml;
    ofSerialize(xml, m_presets);
   
	xml.save(path);
   
}

void GuiManager::saveGuiValues()
{

	ofLogNotice() << "GuiManager::saveGuiValues-> saving values from: " << GUI_SETTINGS_FILE_NAME;

	ofXml xml;
	ofSerialize(xml, m_parameters);

	xml.save(GUI_SETTINGS_FILE_NAME);

}

void GuiManager::loadGuiValues()
{
    
    ofLogNotice() <<"GuiManager::loadGuiValues-> loading values from: " << GUI_SETTINGS_FILE_NAME;
    
    ofXml xml;
	xml.load(GUI_SETTINGS_FILE_NAME);
    
    ofDeserialize(xml, m_parameters);
}



void GuiManager::toggleGui()
{
    m_showGui = !m_showGui;
}

void GuiManager::drawRectangle()
{
    ofPushStyle();
    ofSetColor(15);
    ofDrawRectangle( 0, 0, this->getWidth(), ofGetHeight());
    ofPopStyle();
}









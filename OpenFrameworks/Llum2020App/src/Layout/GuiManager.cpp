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
	this->setupParticlesGui();
	this->setupAudioGui();
    this->setupMidiGui();
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

	m_showMode.set("ShowMode", false);
	m_showMode.addListener(scenesManager, &SceneManager::onShowModeChange);
	m_parameters.add(m_showMode);
	m_scenesGroup.add(m_showMode);

    m_sceneTransitionTime.set("TransitionTime", 2.0, 0.0, 10);
    m_sceneTransitionTime.addListener(scenesManager, &SceneManager::onTransitionTimeChange);
    m_parameters.add(m_sceneTransitionTime);

	m_sceneTimer.set("ScenesTimer", 120, 10, 240.0);
	m_sceneTimer.addListener(scenesManager, &SceneManager::onChangeSceneDuration);
	m_parameters.add(m_sceneTimer);

}

void GuiManager::setupMidiGui()
{
    auto midiManager = &AppManager::getInstance().getMidiManager();
    m_midiGroup.setName("MIDI");
    
    m_midiPitch.set("Pitch", 0, 0, 128);
    m_midiPitch.addListener(midiManager, &MidiManager::setPitch);
    m_presets.add(m_midiPitch);
    m_midiGroup.add(m_midiPitch);
    
    m_midiControl.set("Control", 0, 0, 128);
    m_midiControl.addListener(midiManager, &MidiManager::setControl);
    m_presets.add(m_midiControl);
    m_midiGroup.add(m_midiControl);

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
	m_presets.add(m_gradientMode);



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
	m_presets.add(m_shaderColorMode);

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

void GuiManager::onSceneChange(const string &sceneName)
{
	ofLogNotice() << "GuiManager::onSceneChange << looking for scene: " << sceneName;

	for (int i = 0; i < m_sceneNames.size(); i++) {
		if (m_sceneNames[i] == sceneName) {
			ofLogNotice() << "GuiManager::onSceneChange << Changing to scene: " << sceneName;
			this->onSceneChange(i);
		}
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
    m_presets.add(m_contrast);
    m_postProcessingGroup.add(m_contrast);
    
    m_saturation.set("Saturation", 1.0, 0.0, 2.0);
    m_saturation.addListener(colorManager, &ColorManager::setSaturation);
	m_presets.add(m_saturation);
    m_postProcessingGroup.add(m_saturation);
    
    m_brightness.set("Brightness", 1.0, 0.0, 2.0);
    m_brightness.addListener(colorManager, &ColorManager::setBrightness);
	m_presets.add(m_brightness);
    m_postProcessingGroup.add(m_brightness);
    
    m_gamma.set("Gamma", 1.0, 0.0, 2.0);
    m_gamma.addListener(colorManager, &ColorManager::setGamma);
	m_presets.add(m_gamma);
    m_postProcessingGroup.add(m_gamma);

	m_blur.set("Blur", 0.0, 0.0, 10.0);
	m_blur.addListener(colorManager, &ColorManager::onChangeBlur);
	m_presets.add(m_blur);
	m_postProcessingGroup.add(m_blur);
	
  
    m_minInput.set("MinInput", 0.0, 0.0, 1.0);
    m_minInput.addListener(colorManager, &ColorManager::setMinInput);
	m_presets.add(m_minInput);
    m_postProcessingGroup.add(m_minInput);
    
    m_maxInput.set("MaxInput", 1.0, 0.0, 1.0);
    m_maxInput.addListener(colorManager, &ColorManager::setMaxInput);
	m_presets.add(m_maxInput);
    m_postProcessingGroup.add(m_maxInput);
    
    m_minOutput.set("MinOutput", 0.0, 0.0, 1.0);
    m_minOutput.addListener(colorManager, &ColorManager::setMinOutput);
	m_presets.add(m_minOutput);
    m_postProcessingGroup.add(m_minOutput);
    
    m_maxOutput.set("MaxOutput", 1.0, 0.0, 1.0);
    m_maxOutput.addListener(colorManager, &ColorManager::setMaxOutput);
	m_presets.add(m_maxOutput);
    m_postProcessingGroup.add(m_maxOutput);
}


void GuiManager::setupLedsGui()
{
    auto ledsManager = &AppManager::getInstance().getLedsManager();
    auto sceneManager = &AppManager::getInstance().getSceneManager();
    
    m_ledsGroup.setName("Leds");
    m_ledsSize.set("LedSize", 1.0, 0.0, 20.0);
    m_ledsSize.addListener(ledsManager, &LedsManager::setSize);
    m_ledsGroup.add(m_ledsSize);
    m_parameters.add(m_ledsSize);
    
    m_ledsGrid.set("Grid", false);
    m_ledsGrid.addListener(ledsManager, &LedsManager::setGrid);
    m_ledsGroup.add(m_ledsGrid);
    m_parameters.add(m_ledsGrid);
}

void GuiManager::setupParticlesGui()
{
	auto particlesManager = &AppManager::getInstance().getParticlesManager();

	m_particlesGroup.setName("Particles");

	m_particlesDirection.set("Field Direction", 0.0, 0.0, 360.0);
	m_particlesDirection.addListener(particlesManager, &ParticlesManager::setDirecction);
	m_presets.add(m_particlesDirection);
	m_particlesGroup.add(m_particlesDirection);

	m_particlesDirectionMag.set("Dir. Mag.", 0.0, 0.0, 2.0);
	m_particlesDirectionMag.addListener(particlesManager, &ParticlesManager::setDirecctionMag);
	m_presets.add(m_particlesDirectionMag);
	m_particlesGroup.add(m_particlesDirectionMag);

	m_particlesSpeed.set("Field Speed", 0.0, 0.0, 10.0);
	m_particlesSpeed.addListener(particlesManager, &ParticlesManager::setSpeed);
	m_presets.add(m_particlesSpeed);
	m_particlesGroup.add(m_particlesSpeed);

	m_particlesSize.set("Particle Size", 6.0, 0.0, 200.0);
	m_particlesSize.addListener(particlesManager, &ParticlesManager::setSize);
	m_presets.add(m_particlesSize);
	m_particlesGroup.add(m_particlesSize);

	m_particlesNum.set("NumParticles", 800, 0, 1500);
	m_particlesNum.addListener(particlesManager, &ParticlesManager::setNum);
	m_presets.add(m_particlesNum);
	m_particlesGroup.add(m_particlesNum);

	m_particlesFade.set("Fade", 0.0, 0.0, 60.0);
	m_particlesFade.addListener(particlesManager, &ParticlesManager::setFadeTime);
	m_presets.add(m_particlesFade);
	m_particlesGroup.add(m_particlesFade);

	m_particlesVectSpeed.set("Vect. Speed", 0.2, 0.0, 2.0);
	m_particlesVectSpeed.addListener(particlesManager, &ParticlesManager::setVectorSpeed);
	m_presets.add(m_particlesVectSpeed);
	m_particlesGroup.add(m_particlesVectSpeed);

	m_particlesRandomness.set("Randomness", 0.5, 0.0, 5.0);
	m_particlesRandomness.addListener(particlesManager, &ParticlesManager::setRandonmess);
	m_presets.add(m_particlesRandomness);
	m_particlesGroup.add(m_particlesRandomness);

}


void GuiManager::setupAudioGui()
{
	auto audioManager = &AppManager::getInstance().getAudioManager();

	m_audioGroup.setName("Audio");

	m_audioVolume.set("Volume", 1.0, 0.0, 10.0);
	m_audioVolume.addListener(audioManager, &AudioManager::onChangeVolume);
	m_parameters.add(m_audioVolume);
	m_audioGroup.add(m_audioVolume);

	m_audioThreshold.set("Threshold", 0.5, 0.0, 1.0);
	m_audioThreshold.addListener(audioManager, &AudioManager::onChangeThreshold);
	m_parameters.add(m_audioThreshold);
	m_audioGroup.add(m_audioThreshold);

	m_audioSmoothing.set("Smoothing", 0.5, 0.0, 1.0);
	m_audioSmoothing.addListener(audioManager, &AudioManager::onChangeSmoothing);
	m_parameters.add(m_audioSmoothing);
	m_audioGroup.add(m_audioSmoothing);

	m_audioLow.set("Low", 0.0, 0.0, 1.0);
	m_audioGroup.add(m_audioLow);

	m_audioMid.set("Mid", 0.0, 0.0, 1.0);
	m_audioGroup.add(m_audioMid);

	m_audioHigh.set("High", 0.0, 0.0, 1.0);
	m_audioGroup.add(m_audioHigh);

	m_audioLowOnset.set("Low", false);
	m_audioGroup.add(m_audioLowOnset);

	m_audioMidOnset.set("Mid", false);
	m_audioGroup.add(m_audioMidOnset);

	m_audioHighOnset.set("High", false);
	m_audioGroup.add(m_audioHighOnset);
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
            
			if (ImGui::Button("Save Gui"))
			{
				this->saveGuiValues();
			}

			if (ImGui::Button("Load Gui"))
			{
				this->loadGuiValues();
			}
           
            if (ofxImGui::BeginTree(m_scenesGroup, mainSettings))
            {
				ofxImGui::AddParameter(m_showMode);
                ofxImGui::AddParameter(m_sceneTransitionTime);
				ofxImGui::AddParameter(m_sceneTimer);
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
				ofxImGui::AddGroup(m_ledsGroup, mainSettings);
                ofxImGui::EndTree(mainSettings);
            }

            
            if (ofxImGui::BeginTree(m_postProcessingGroup, mainSettings))
            {
                //auto & group =
				ofxImGui::AddGroup(m_postProcessingGroup, mainSettings);
                ofxImGui::EndTree(mainSettings);
            }
            
            if (ofxImGui::BeginTree(m_shadersGroup, mainSettings))
            {
                //auto & group =
				ofxImGui::AddGroup(m_shadersGroup, mainSettings);           
                ofxImGui::EndTree(mainSettings);
            }

			if (ofxImGui::BeginTree(m_audioGroup, mainSettings))
			{
				//auto & group =
				ofxImGui::AddGroup(m_audioGroup, mainSettings);
				ofxImGui::EndTree(mainSettings);
			}
            
            if (ofxImGui::BeginTree(m_midiGroup, mainSettings))
            {
                //auto & group =
                ofxImGui::AddGroup(m_midiGroup, mainSettings);
                ofxImGui::EndTree(mainSettings);
            }

			if (ofxImGui::BeginTree(m_particlesGroup, mainSettings))
			{
				//auto & group =
				ofxImGui::AddGroup(m_particlesGroup, mainSettings);
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









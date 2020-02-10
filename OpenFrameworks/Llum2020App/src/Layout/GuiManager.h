/*
 *  GuiManager.h
 *  Llum 2020 App
 *
 *  Created by Imanol Gomez on 01/02/20.
 *
 */


#pragma once

#include "Manager.h"
#include "ofxImGui.h"


//========================== class GuiManager ==============================
//============================================================================
/** \class GuiManager GuiManager.h
 *    \brief Class managing the application´s grapical user interface (GUI)
 *    \details It creates the gui and the callback functions that will be affected
 *    by the gui
 */

class GuiManager: public Manager
{
    static const string GUI_SETTINGS_FILE_NAME;
	static const string GUI_SETTINGS_FILE_PATH;
    static const string GUI_SETTINGS_NAME;
    static const int GUI_WIDTH;
    
public:
    
    //! Constructor
    GuiManager();
    
    //! Destructor
    ~GuiManager();
    
    //! Set-up the gui
    void setup();
    
    //! update the gui
    void update();
    
    //! Draw the gui
    void draw();
    
    void savePresets(string path = "");
    
    void loadPresets(string path = "");
    
    void toggleGui();
    
    void showGui(bool show){m_showGui=show;}
    
    int getWidth() {return m_width;}
    
    int getHeight() {return m_height;}
    
    ofPoint  getPosition() {return m_position;}

    float getLedsSize() const {return m_ledsSize;}
    
    void setVideoPath(const string& path) {m_videoPath = ofToDataPath(path);}
    
    void setupScenesGui();
    
    void onSceneChange(int sceneIndex);

	void onSceneChange(const string& sceneName);
    
    void onVideoChange(int videoIndex);
    
    float getShaderSpeed() const {return m_shaderSpeed.get();}
    
    float getShaderParameter() const{return m_shaderParameter.get();}
    
    float getColorAmount() const{return m_colorAmount.get();}
 
    int getShaderDirection() const {return m_shaderDirection.get();}

    void setSceneTransitionTime(float value) {m_sceneTransitionTime = value;}

    void setColorCorrectionType(int value){m_shaderColorMode = value;}

	void setAudioLow(float value) { m_audioLow = value; }

	void setAudioMid(float value) { m_audioMid = value; }

	void setAudioHigh(float value) { m_audioHigh = value; }

	void setAudioLowOnset(bool value) { m_audioLowOnset = value; }

	void setAudioMidOnset(bool value) { m_audioMidOnset = value; }

	void setAudioHighOnset(bool value) { m_audioHighOnset = value; }

	bool getShowMode() const { return m_showMode.get(); }

private:
    
    void setupGuiParameters();
    
    void drawRectangle();
    
    void drawGui();

	void setupAudioGui();
    
    void setupVideoGui();

	void setupColorsGui();
    
    void setupShadersGui();
    
    void setupModesGui();
    
    void setupLedsGui();

	void setupParticlesGui();

    void setupProcessingGroup();
    
    void updateSize(const ofxImGui::Settings& settings);

	void saveGuiValues();

	void loadGuiValues();

    
private:
    
    ofxImGui::Gui   m_gui;
        
    
    ofParameterGroup      m_parameters;
	ofParameterGroup      m_presets;
    
    ofParameterGroup m_modeGroup;
    ofParameterGroup m_videoGroup;
    ofParameterGroup m_ledsGroup;
	ofParameterGroup m_colorsGroup;
    ofParameterGroup m_scenesGroup;
    ofParameterGroup m_postProcessingGroup;
    ofParameterGroup m_shadersGroup;
	ofParameterGroup m_particlesGroup;
	ofParameterGroup m_audioGroup;
    ofParameterGroup m_communicationsGroup;

	
	ofParameter<bool>       m_showMode;
    ofParameter<float>      m_sceneTransitionTime;
	ofParameter<float>      m_sceneTimer;
    ofParameter<float>      m_shaderSpeed;
    ofParameter<float>      m_shaderParameter;
    ofParameter<float>      m_colorAmount;
    ofParameter<int>        m_shaderDirection;

	ofParameter<float>      m_audioSmoothing;
	ofParameter<float>      m_audioThreshold;
	ofParameter<float>      m_audioVolume;
	ofParameter<float>      m_audioLow;
	ofParameter<float>      m_audioMid;
	ofParameter<float>      m_audioHigh;
	ofParameter<bool>       m_audioLowOnset;
	ofParameter<bool>       m_audioMidOnset;
	ofParameter<bool>       m_audioHighOnset;
    
    
    ofParameter<string>     m_videoPath;
    ofParameter<int>        m_viewMode;
    ofParameter<int>        m_sceneMode;
	ofParameter<int>        m_gradientMode;
	ofParameter<int>        m_shaderColorMode;
    ofParameter<float>      m_ledsSize;
    ofParameter<bool>       m_ledsGrid;
    
    ofParameter<int>        m_maxDataPacketSize;
    
    ofParameter<ofFloatColor>	m_solidColor;
    
    std::vector<std::string>    m_sceneNames;
	std::vector<std::string>    m_gradientNames;
	std::vector<std::string>    m_shaderColorNames;
    
    ofParameter<float>      m_contrast;
    ofParameter<float>      m_saturation;
    ofParameter<float>      m_brightness;
    ofParameter<float>      m_gamma;
    ofParameter<float>      m_minInput;
    ofParameter<float>      m_maxInput;
    ofParameter<float>      m_minOutput;
    ofParameter<float>      m_maxOutput;
    ofParameter<float>      m_blur;

	ofParameter<float>      m_particlesDirection;
	ofParameter<float>      m_particlesDirectionMag;
	ofParameter<float>      m_particlesSpeed;
	ofParameter<float>      m_particlesSize;
	ofParameter<float>      m_particlesFade;
	ofParameter<int>        m_particlesNum;
	ofParameter<float>      m_particlesVectSpeed;
	ofParameter<float>      m_particlesRandomness;
	ofParameter<float>      m_particlesBlur;
    
    float m_width, m_height;
    ofPoint   m_position;
    
    bool        m_showGui;  //It defines the whether the gui should be shown or not
};

//==========================================================================



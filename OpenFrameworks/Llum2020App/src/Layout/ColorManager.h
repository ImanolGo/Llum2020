/*
 *  ColorManager.h
 *  Llum 2020 App
 *
 *  Created by Imanol Gomez on 01/02/20.
 *
 */




#pragma once

#include "Manager.h"
#include "ofxBlur.h"

//========================== class ColorManager ==============================
//============================================================================
/** \class ColorManager ColorManager.h
 *	\brief Class managing the colors of the application
 *	\details It saves the current monochromatic color as well as gradients
 */


class ColorManager: public Manager
{
	enum Shader_Type { PASS = 0, HUE, GRADIENT };


	static const string GRADIENTS_PATH;
    
public:
    
   
    //! Constructor
    ColorManager();

    //! Destructor
    ~ColorManager();

    //! Set-up the layout
    void setup();
    
    //! Update the layout
    void update();
    
    //! Draw the layout
    void draw();
    
	void setUseHueCorrection(bool & value) { m_useHueCorrection = value; }

	void setSolidColor(ofFloatColor & value) { m_solidColor = value; }

	bool getUseHueCorrection() { return m_useHueCorrection; }

	ofFloatColor getSolidColor() const { return m_solidColor; }
    
	const vector<pair<string, ofImage>> & getGradients() const { return m_gradients; }

	const vector<string> getShaderColorNames() { return m_shaderColorNames; }

	void changeGradientIndex(int& index);

	void changeShaderType(int& index);

	ofTexture & getGradient() { return m_mainGradient; }

	ofFbo & getFboGradient() { return m_gradientFbo; }

	void onChangeBlur(float& value);

	void setupBlur();

	void beginBlur();

	void endBlur();

	void beginColorLevels();

	void endColorLevels();

	void beginColorCorrection();

	void endColorCorrection();

	void setContrast(float& value) {m_contrast = value; }

	void setSaturation(float& value) {m_saturation = value; }

	void setBrightness(float& value) {m_brightness = value; }

	void setGamma(float& value) {m_gamma = value; }

	void setMinInput(float& value) {m_minInput = value; }

	void setMaxInput(float& value) {m_maxInput = value; }

	void setMinOutput(float& value) {m_minOutput = value; }

	void setMaxOutput(float& value) {m_maxOutput = value; }



private:

	void setupGradients();

	void setupFbo();

	void setupColorCorrectionShader(const string& name);

	void setupShaders();

	void setupColorLevelShader();




private:

	ofxBlur							m_blur;
	bool							m_useHueCorrection;
	ofFloatColor					m_solidColor;
	vector<pair<string, ofImage>>   m_gradients;
	ofTexture						m_mainGradient;
	ofShader						m_shaderColorCorrection, m_shaderLevelCorrection;
	vector<std::string>				m_shaderColorNames;
	ofFbo							m_gradientFbo;

	float m_contrast;
	float m_saturation;
	float m_brightness;
	float m_gamma;
	float m_minInput;
	float m_maxInput;
	float m_minOutput;
	float m_maxOutput;
};

//==========================================================================



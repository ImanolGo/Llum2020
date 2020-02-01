/*
 *  ColorManager.cpp
 *  Llum 2020 App
 *
 *  Created by Imanol Gomez on 01/02/20.
 *
 */




#include "ofMain.h"

#include "ColorManager.h"
#include "AppManager.h"


const string ColorManager::GRADIENTS_PATH = "images/gradients/";

ColorManager::ColorManager(): Manager(), m_useHueCorrection(false), m_contrast(1.0), m_saturation(1.0), m_brightness(1.0), m_gamma(1.0), m_minInput(0.0), m_maxInput(0.0), m_minOutput(0.0), m_maxOutput(1.0)
{
	//Intentionally left empty
}


ColorManager::~ColorManager()
{
    ofLogNotice() <<"ColorManager::Destructor";
}


void ColorManager::setup()
{
	if(m_initialized)
		return;

    ofLogNotice() <<"ColorManager::initialized";
	
	this->setupGradients();
	this->setupShaders();
	this->setupFbo();

	m_shaderColorNames = {"Original", "Hue", "Gradient"};


	Manager::setup();
	 
}

void ColorManager::setupShaders()
{
	this->setupColorCorrectionShader("ColorPassShader");
	this->setupColorLevelShader();
}

void ColorManager::setupColorLevelShader()
{
	string path = "shaders/ColorLevelShader";

	m_shaderLevelCorrection.unload();
	if (m_shaderLevelCorrection.load(path))
	{
		ofLogNotice() << "SceneManager::setupColorLevelShader-> successfully loaded " << path;
	}
	else {
		ofLogNotice() << +"SceneManager::setupColorLevelShader-> Cannot load " << path;
	}
}

void ColorManager::setupColorCorrectionShader(const string& name)
{
	string path = "shaders/" + name;

	m_shaderColorCorrection.unload();
	if (m_shaderColorCorrection.load(path))
	{
		ofLogNotice() << "SceneManager::setupColorCorrectionShader-> successfully loaded " << path;
	}
	else {
		ofLogNotice() << +"SceneManager::setupColorCorrectionShader-> Cannot load " << path;
	}
}

void ColorManager::setupFbo()
{
	float width = AppManager::getInstance().getSettingsManager().getAppWidth();
	float height = AppManager::getInstance().getSettingsManager().getAppHeight();

	m_gradientFbo.allocate(width, height, GL_RGBA);
	m_gradientFbo.begin(); ofClear(0); m_gradientFbo.end();
}

void ColorManager::changeShaderType(int& index)
{
	switch (index)
	{
		case PASS:
			this->setupColorCorrectionShader("ColorPassShader");
			break;
		case HUE:
			this->setupColorCorrectionShader("ColorHueShader");
			break;
		case GRADIENT:
			this->setupColorCorrectionShader("ColorGradientShader");
			break;
	}
}

void ColorManager::update()
{

}


void ColorManager::draw()
{
	m_mainGradient.draw(300, 300);
}

void ColorManager::beginColorCorrection()
{
	m_shaderColorCorrection.begin();
	m_shaderColorCorrection.setUniform4f("color", m_solidColor);
	m_shaderColorCorrection.setUniformTexture("texGradient", m_gradientFbo.getTexture(), 1);

}

void ColorManager::endColorCorrection()
{
	m_shaderColorCorrection.end();
}

void ColorManager::beginColorLevels()
{
	m_shaderLevelCorrection.begin();
	// csb params
	m_shaderLevelCorrection.setUniform1f("contrast", m_contrast);
	m_shaderLevelCorrection.setUniform1f("saturation", m_saturation);
	m_shaderLevelCorrection.setUniform1f("brightness", m_brightness);
	// levels params
	m_shaderLevelCorrection.setUniform1f("gamma", m_gamma);
	m_shaderLevelCorrection.setUniform1f("minInput", m_minInput);
	m_shaderLevelCorrection.setUniform1f("maxInput", m_maxInput);
	m_shaderLevelCorrection.setUniform1f("minOutput", m_minOutput);
	m_shaderLevelCorrection.setUniform1f("maxOutput", m_maxOutput);
}

void ColorManager::endColorLevels()
{
	m_shaderLevelCorrection.end();
}

void ColorManager::setupGradients()
{
	m_mainGradient.allocate(100, 100, OF_IMAGE_COLOR);

	ofDirectory dir(GRADIENTS_PATH);
	if (!dir.exists()) {
		ofLogNotice() << "ColorManager::setupGradients -> Folder not found: " << GRADIENTS_PATH;
		return;
	}

	//only show image files
	dir.allowExt("png");
	dir.allowExt("jpg");
	dir.allowExt("jpeg");

	if( dir.listDir() == 0){
	    ofLogNotice() <<"ColorManager::setupGradients -> No image files found in: " << GRADIENTS_PATH;
	    return;
	}

	dir.sort();


	for (int i = 0; i < dir.size(); i++)
	{
		ofImage image;

		if (image.load(dir.getPath(i))) {
			pair<string, ofImage> gradient(dir.getName(i), image);
			m_gradients.push_back(gradient);
			ofLogNotice() << "ColorManager::setupGradients -> Loaded image " << dir.getName(i);
		}
	}

	if (!m_gradients.empty()) {
		int ind = 0;
		this->changeGradientIndex(ind);
	}

}


void ColorManager::changeGradientIndex(int& index)
{
	if (index < 0 || index >= m_gradients.size()) {
		return;
	}

	ofLogNotice() << "ColorManager::changeGradientIndex << scene index " << index;


	ofTextureData texData;
	texData.width = m_gradients[index].second.getWidth();
	texData.height = m_gradients[index].second.getHeight();
	texData.textureTarget = GL_TEXTURE_2D;
	texData.bFlipTexture = true;
	m_mainGradient.allocate(texData);
	m_mainGradient.loadData(m_gradients[index].second.getPixels());

	m_gradientFbo.begin(); 
		m_mainGradient.draw(0,0,m_gradientFbo.getWidth(), m_gradientFbo.getHeight());
	m_gradientFbo.end();



	//m_mainGradient = m_gradients[index].second;

}



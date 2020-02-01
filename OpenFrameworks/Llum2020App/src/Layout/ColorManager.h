/*
 *  ColorManager.h
 *  Llum 2020 App
 *
 *  Created by Imanol Gomez on 01/02/20.
 *
 */




#pragma once

#include "Manager.h"

//========================== class ColorManager ==============================
//============================================================================
/** \class ColorManager ColorManager.h
 *	\brief Class managing the colors of the application
 *	\details It saves the current monochromatic color as well as gradients
 */


class ColorManager: public Manager
{

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

	void changeGradientIndex(int& index);

	ofImage & getGradient() { return m_mainGradient; }



private:

	void setupGradients();


private:

	bool                     m_useHueCorrection;
	ofFloatColor			 m_solidColor;
	vector<pair<string, ofImage>>     m_gradients;
	ofImage					m_mainGradient;
};

//==========================================================================



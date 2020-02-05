/*
 *  ModelManager.h
 *  Llum 2020 App
 *
 *  Created by Imanol Gomez on 01/02/20.
 *
 */



#pragma once

#include "Manager.h"

//========================== class ModelManager ==============================
//============================================================================
/** \class ModelManager ModelManager.h
 *	\brief Class managing the model visuals
 *	\details it creates and updates the 3D model visuals
 */


class ModelManager: public Manager
{
    public:

        //! Constructor
        ModelManager();

        //! Destructor
        ~ModelManager();

        //! Setup the Model Manager
        void setup();

        //! Update the Model Manager
        void update();

        //! Draw the Model Manager
        void draw();
    
        void resetCamera();
    
        void setControlArea(ofRectangle& rect) {m_camera.setControlArea(rect);}

    private:


    
    private:
    
        ofEasyCam m_camera; // add mouse controls for camera movement
    
        ofFbo     m_fbo;

    

};

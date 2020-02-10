/*
 *  BasicVisual.h
 *
 *  Created by Imanol Gomez on 16/02/15.
 *
 */

#pragma once

#include "ofMain.h"

//=============================== class BasicVisual ==============================
//===========================================================================
/** \class BasicVisual BasicVisuals.h
 *  \brief Base class for all BasicVisuals
 *  \details Gives basic functionalities for all objects to be rendered
 */

class BasicVisual
{
    public:

        //! Constructor
        BasicVisual():m_width(0), m_height(0), m_position(glm::vec3(0,0,0)), m_scale(glm::vec3(1,1,1)) {}
    
        //! Constructor
        BasicVisual(const glm::vec3& pos, float width, float height): m_position(pos), m_width(width), m_height(height), m_scale(glm::vec3(1,1,1)) {}

        //! Destructor
        virtual ~BasicVisual(){}

        //! Draws the BasicVisual
        virtual void draw(){}

        //! Changes the alpha channel.
        virtual void setAlpha(double alpha) { m_color.set(m_color.r,m_color.g,m_color.b,alpha);}

        //! Changes the alpha channel.
        virtual double getAlpha() const{ return m_color.a;}

        //! Sets the color of the BasicVisual
        virtual void setColor(const ofColor& color) {m_color = color;}

        //! Gets the color of the BasicVisual
        virtual const ofColor& getColor() {return m_color;}

        //! Gets the position of the BasicVisual
        virtual const ofPoint& getPosition() const{ return m_position;}

        //! Sets the position of the BasicVisual
        virtual void setPosition(const ofPoint& pos) {m_position = pos;}

        //! Sets the scale factor of the BasicVisual
        virtual void setScale(const glm::vec3& scale) {m_scale = scale;}

        //! Gets the scale factor of the BasicVisual
        virtual const glm::vec3& getScale() const{ return m_scale;}

         //! Sets the rotation of the BasicVisual
        virtual void setRotation(const glm::vec3& rotation) {m_rotation = rotation;}

        //! Gets the rotation of the BasicVisual
        virtual const glm::vec3& getRotation() const{ return m_rotation;}

        //! Get the width
        virtual float getWidth()const {return m_width;}

        //! Get the height
        virtual float getHeight()const {return m_height;}

        //! Set width
        virtual void setWidth(float width) {m_width = width;}

        //! Set width
        virtual void setHeight(float height) {m_height = height;}
    
        //! Sets the value.
        virtual float getValue() const{ return m_value;}
    
        //! Changes the value.
        virtual void setValue(float value) {m_value = value;}

    protected:

		glm::vec3			m_position;     ///< defines the position of the BasicVisual
        float				m_width;        ///< the width of the BasicVisual
        float				m_height;       ///< the height of the BasicVisual
        ofColor				m_color;        ///< color of the BasicVisual
		glm::vec3			 m_scale;        ///< saves the current scale factor
		glm::vec3			m_rotation;     ///< saves the current rotation
        float				m_value;        ///< saves a float value for any kind of anmation


    };




/*
 *  VisualEffects.h
 *
 *  Created by Imanol G—mez on 16/02/15.
 *
 */

#pragma once


#include "ofMain.h"

class BasicVisual;

typedef enum  {
	LINEAR,
	EXPONENTIAL,
	QUADRATIC,
	CUBIC,
	SINUSOIDAL,
	QUARTIC,
	QUINTIC,
	CIRCULAR
} EasingFunction;

typedef enum  {
	EASE_IN,
	EASE_OUT,
	EASE_IN_OUT
} EasingType;


//==============================================================================
/** \class VisualEffect VisualEffect.h
 *	\brief Base class for all the visual effects.
 *	\details Provides basic member attributes which are in common for all
 *           visual effects.
 */
//==============================================================================

class VisualEffect
{
public:

	//! Constructor
	VisualEffect(shared_ptr<BasicVisual> visual, EasingFunction function = LINEAR, EasingType type = EASE_IN);

	//! Destructor
	virtual ~VisualEffect(){}

	//! Updates the elapsed time and visual effect parameters
	virtual void update() = 0;

	//! Starts the visual effect
	virtual void start(double startTime = 0.0);

	//! Stops the visual effect
	virtual void stop();

    //! Finishes the visual effect
	virtual void finish();

	//! Returns the shared pointer associated with the visual effect
	shared_ptr<BasicVisual> getVisual() { return m_visual; }

	//! Returns the name with the visual effect
	const string& getName() { return m_name; }

    //! Returns the current state of the animation
	bool isActive() const { return m_isActive; }
    
    //! Returns if the animation is finished
    bool isFinished() const { return m_isFinished; }

	//! Set the elapsed time before the start of the animation
	void setElapsedTimeToStart(double time) { m_elaspedTimeToStart = time; }


protected:

	//! Returns the update value from the selected function.
	//! t: current time, from: start value, to: end value, duration: the total animation time
	double function(double t, double from, double to, double duration) const;

protected:

	shared_ptr<BasicVisual>     	m_visual;				///< stores the visual as a shared pointer (shared_ptr)
	bool					m_isActive;				///< determines whether an animation is currently updated or not
    bool					m_isFinished;           ///< determines whether an animation is finished
	double					m_animationTime;		///< duration of the animation in ms
	double					m_elapsedTime;			///< elapsed time since the last update
	EasingFunction			m_function;				///< saves what kind of easing function do you want to use
	EasingType				m_type;					///< saves what type of easing you want
	double					m_startTime;			///< start time of the animation
	double					m_elaspedTimeToStart;	///< elapsed time before the start of the animation
	string                  m_name;                 ///< name of the visual effect

};


//==============================================================================
/** \class FadeVisual VisualEffects.h
 *	\brief Fade effect class for visuals.
 *	\details Provides basic member attributes and methods
 *			 to provide visuals fading.
 */
//==============================================================================

class FadeVisual: public VisualEffect
{
public:

	//! Constructor
	FadeVisual(shared_ptr<BasicVisual> visual, EasingFunction function = LINEAR, EasingType type = EASE_IN);


    //========================= Fade Interface ================================

	//! updates the fade visual if active
	virtual void update();


    //==============================================================================

    //! Sets the final alpha value and the duration of the animation
	virtual void setParameters(double endAlpha, double animationTime);

	//! Sets the starting and final alpha value and the duration of the animation
	virtual void setParameters(double startAlpha,double endAlpha, double animationTime);


protected:

    float	m_alpha;            ///< current alpha value
	double	m_startAlpha;		///< start alpha value
	double	m_endAlpha;         ///< end alpha value


};


//==============================================================================
/** \class ScaleVisual VisualEffects.h
 *	\brief Scale effect class for visuals.
 *	\details Provides basic member attributes and methods
 *			 to provide visuals scaling animations.
 */
//==============================================================================

class ScaleVisual: public VisualEffect
{
public:

	//! Constructor
	ScaleVisual(shared_ptr<BasicVisual> visual, EasingFunction function = LINEAR, EasingType type = EASE_IN);


    //========================= Fade Interface ================================

	//! updates the fade visual if active
	virtual void update();

    //==============================================================================

    //! Sets the final scale value and the duration of the animation
	virtual void setParameters(const glm::vec3& endScale, double animationTime);

	//! Sets the starting and final scale value and the duration of the animation
	virtual void setParameters(const glm::vec3& startScale,const glm::vec3& endScale, double animationTime);


protected:

	glm::vec3	m_startScale;		///< start scale value
	glm::vec3	m_endScale;         ///< end scale value
    glm::vec3	m_scale;            ///< stores the current scale

};



//==============================================================================
/** \class MoveVisual VisualEffects.h
 *	\brief Move effect class for visuals.
 *	\details Provides basic member attributes and methods
 *			 to provide visuals moving aniamtions.
 */
//==============================================================================

class MoveVisual: public VisualEffect
{
public:

	//! Constructor
	MoveVisual(shared_ptr<BasicVisual> visual, EasingFunction function = LINEAR, EasingType type = EASE_IN);


    //========================= Fade Interface ================================

	//! updates the fade visual if active
	virtual void update();


    //==============================================================================

    //! Sets the final position and the duration of the animation
	virtual void setParameters(const glm::vec3& endPos, double animationTime);

	//! Sets the starting and final position and the duration of the animation
	virtual void setParameters(const glm::vec3& startPos,const glm::vec3& endPos, double animationTime);


protected:

	glm::vec3	m_startPos;		///< start position
	glm::vec3	m_endPos;       ///< end position
    glm::vec3	m_pos;          ///< stores the current position

};

//==============================================================================
/** \class ColorEffect VisualEffects.h
 *	\brief Color effect class for visuals.
 *	\details Provides basic member attributes and methods
 *			 to provide vclor changing animations
 */
//==============================================================================

class ColorEffect: public VisualEffect
{
public:

	//! Constructor
	ColorEffect(shared_ptr<BasicVisual> visual, EasingFunction function = LINEAR, EasingType type = EASE_IN);


    //========================= Color Effect Interface ================================

	//! updates the fade visual if active
	virtual void update();


    //==============================================================================

    //! Sets the final position and the duration of the animation
	virtual void setParameters(const ofColor& endColor, double animationTime);

	//! Sets the starting and final position and the duration of the animation
	virtual void setParameters(const ofColor& startColor,const ofColor& endColor, double animationTime);


protected:

	ofColor	m_startColor;	  ///< start color
	ofColor	m_endColor;       ///< end color
    ofColor	m_color;          ///< stores the current color

};


//==============================================================================
/** \class ValueEffect VisualEffects.h
 *    \brief Value animation class for visuals.
 *    \details Provides basic member attributes and methods
 *             to provide value animations.
 */
//==============================================================================

class ValueEffect: public VisualEffect
{
public:
    
    //! Constructor
    ValueEffect(shared_ptr<BasicVisual> visual, EasingFunction function = LINEAR, EasingType type = EASE_IN);
    
    
    //========================= Fade Interface ================================
    
    //! updates the fade visual if active
    virtual void update();
    
    
    //==============================================================================
    
    //! Sets the final alpha value and the duration of the animation
    virtual void setParameters(double end, double animationTime);
    
    //! Sets the starting and final alpha value and the duration of the animation
    virtual void setParameters(double start,double end, double animationTime);
    
    
protected:
    
    float    m_value;        ///< current  value
    double    m_start;        ///< start  value
    double    m_end;         ///< end  value
    
    
};



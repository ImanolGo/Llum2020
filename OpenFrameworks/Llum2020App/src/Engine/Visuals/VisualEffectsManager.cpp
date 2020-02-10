/*
 *  VisualEffectsManager.cpp
 *
 *  Created by Imanol GÑmez on 16/02/15.
 *
 */

#include "VisualEffectsManager.h"

VisualEffectsManager::VisualEffectsManager(): Manager()
{
    // intentionally left empty
}


VisualEffectsManager::~VisualEffectsManager()
{
    ofLogNotice() <<"VisualEffectsManager::destructor";
}


void VisualEffectsManager::setup()
{
    if(m_initialized)
        return;
    
    Manager::setup();
    
    ofLogNotice() <<"VisualEffectsManager::initialized";
}

void VisualEffectsManager::update()
{
    for(VisualEffectVector::iterator it = m_visualEffects.begin(); it != m_visualEffects.end();)
    {
        (*it)->update();
        
        
        if((*it)->isFinished()) {
            it = m_visualEffects.erase(it);
        }
        else{
            ++it;
        }
    }
}

void VisualEffectsManager::addVisualEffect(shared_ptr<VisualEffect> visualEffect)
{
    if(!visualEffect)
        return;
    
    for(VisualEffectVector::iterator it = m_visualEffects.begin(); it != m_visualEffects.end();it++) {
        if(*it == visualEffect) {
            return;
        }
    }
    m_visualEffects.push_back(visualEffect);
}

void VisualEffectsManager::removeVisualEffect(shared_ptr<VisualEffect> visualEffect)
{
    if(!visualEffect)
        return;
    
    for(VisualEffectVector::iterator it = m_visualEffects.begin(); it != m_visualEffects.end();)
    {
        if(*it == visualEffect) {
            it = m_visualEffects.erase(it);
        }
        else{
            ++it;
        }
    }
}

void VisualEffectsManager::removeAllVisualEffects(shared_ptr<BasicVisual> visual)
{
    for(VisualEffectVector::iterator it = m_visualEffects.begin(); it != m_visualEffects.end();) {
        if((*it)->getVisual() == visual) {
            it = m_visualEffects.erase(it);
        }
        else {
            ++it;
        }
    }
}

void VisualEffectsManager::removeVisualEffects(shared_ptr<BasicVisual> visual, const string& visualEffectName)
{
    for(VisualEffectVector::iterator it = m_visualEffects.begin(); it != m_visualEffects.end();) {
        if((*it)->getVisual() == visual && (*it)->getName() == visualEffectName) {
            it = m_visualEffects.erase(it);
        }
        else {
            ++it;
        }
    }
}

void VisualEffectsManager::createFadeEffect(shared_ptr<BasicVisual> visual, double startAlpha,double endAlpha, EffectSettings& settings)
{
    if(!visual)
        return;
    
    shared_ptr<FadeVisual> fadeVisual = shared_ptr<FadeVisual>(new FadeVisual(visual,settings.function, settings.type));
    fadeVisual->setParameters(startAlpha,endAlpha,settings.animationTime);
    fadeVisual->start(settings.startAnimation);
    this->addVisualEffect(fadeVisual);
}

void VisualEffectsManager::createFadeEffect(shared_ptr<BasicVisual> visual, double endAlpha, EffectSettings& settings)
{
    if(!visual)
        return;
    
    shared_ptr<FadeVisual> fadeVisual = shared_ptr<FadeVisual>(new FadeVisual(visual,settings.function, settings.type));
    fadeVisual->setParameters(endAlpha,settings.animationTime);
    fadeVisual->start(settings.startAnimation);
    this->addVisualEffect(fadeVisual);
}

void VisualEffectsManager::createValueEffect(shared_ptr<BasicVisual> visual, double start,double end, EffectSettings& settings)
{
    if(!visual)
        return;
    
    shared_ptr<ValueEffect> valueEffect = shared_ptr<ValueEffect>(new ValueEffect(visual,settings.function, settings.type));
    valueEffect->setParameters(start,end,settings.animationTime);
    valueEffect->start(settings.startAnimation);
    this->addVisualEffect(valueEffect);
}



void VisualEffectsManager::createValueEffect(shared_ptr<BasicVisual> visual, double end, EffectSettings& settings)
{
    if(!visual)
        return;
    
    shared_ptr<ValueEffect> valueEffect = shared_ptr<ValueEffect>(new ValueEffect(visual,settings.function, settings.type));
    valueEffect->setParameters(end,settings.animationTime);
    valueEffect->start(settings.startAnimation);
    this->addVisualEffect(valueEffect);
}


void VisualEffectsManager::createScaleEffect(shared_ptr<BasicVisual> visual, const glm::vec3& startScale,const glm::vec3& endScale, EffectSettings& settings)
{
    if(!visual)
        return;
    
    shared_ptr<ScaleVisual> scaleVisual = shared_ptr<ScaleVisual>(new ScaleVisual(visual,settings.function, settings.type));
    scaleVisual->setParameters(startScale,endScale,settings.animationTime);
    scaleVisual->start(settings.startAnimation);
    this->addVisualEffect(scaleVisual);
}

void VisualEffectsManager::createScaleEffect(shared_ptr<BasicVisual> visual, const glm::vec3& endScale, EffectSettings& settings)
{
    if(!visual)
        return;
    
    shared_ptr<ScaleVisual> scaleVisual = shared_ptr<ScaleVisual>(new ScaleVisual(visual, settings.function, settings.type));
    scaleVisual->setParameters(endScale,settings.animationTime);
    scaleVisual->start(settings.startAnimation);
    this->addVisualEffect(scaleVisual);
}

void VisualEffectsManager::popUpAnimation(shared_ptr<BasicVisual> visual, EffectSettings& settings)
{
    if(!visual)
        return;
    
    glm::vec3 startScale(0,0,0);
    glm::vec3 endScale(1,1,1);
    
    shared_ptr<ScaleVisual> scaleVisual = shared_ptr<ScaleVisual>(new ScaleVisual(visual, settings.function, EASE_IN));
    scaleVisual->setParameters(startScale,endScale*1.1,settings.animationTime*0.5);
    scaleVisual->start(settings.startAnimation);
    this->addVisualEffect(scaleVisual);
    
    scaleVisual = shared_ptr<ScaleVisual>(new ScaleVisual(visual, settings.function, EASE_OUT));
    scaleVisual->setParameters(endScale*1.1,endScale,settings.animationTime*0.5);
    scaleVisual->start(settings.startAnimation+settings.animationTime*0.5);
    this->addVisualEffect(scaleVisual);
}

void VisualEffectsManager::createMoveEffect(shared_ptr<BasicVisual> visual, const glm::vec3& startPos,const glm::vec3& endPos, EffectSettings& settings)
{
    if(!visual)
        return;
    
    shared_ptr<MoveVisual> moveVisual = shared_ptr<MoveVisual>(new MoveVisual(visual, settings.function, settings.type));
    moveVisual->setParameters(startPos,endPos,settings.animationTime);
    moveVisual->start(settings.startAnimation);
    this->addVisualEffect(moveVisual);
}

void VisualEffectsManager::createMoveEffect(shared_ptr<BasicVisual> visual, const glm::vec3& endPos, EffectSettings& settings)
{
    if(!visual)
        return;
    
    shared_ptr<MoveVisual> moveVisual = shared_ptr<MoveVisual>(new MoveVisual(visual, settings.function, settings.type));
    moveVisual->setParameters(endPos,settings.animationTime);
    moveVisual->start(settings.startAnimation);
    this->addVisualEffect(moveVisual);
}


void VisualEffectsManager::createColorEffect(shared_ptr<BasicVisual> visual,const ofColor& startColor,const ofColor& endColor, EffectSettings& settings)
{
    if(!visual)
        return;
    
    shared_ptr<ColorEffect> colorEffect = shared_ptr<ColorEffect>(new ColorEffect(visual, settings.function, settings.type));
    colorEffect->setParameters(startColor,endColor,settings.animationTime);
    colorEffect->start(settings.startAnimation);
    this->addVisualEffect(colorEffect);
}

void VisualEffectsManager::createColorEffect(shared_ptr<BasicVisual> visual, const ofColor& endColor, EffectSettings& settings)
{
    if(!visual)
        return;
    
    shared_ptr<ColorEffect> colorEffect = shared_ptr<ColorEffect>(new ColorEffect(visual, settings.function, settings.type));
    colorEffect->setParameters(endColor,settings.animationTime);
    colorEffect->start(settings.startAnimation);
    this->addVisualEffect(colorEffect);
}








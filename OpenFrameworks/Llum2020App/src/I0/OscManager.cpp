/*
 *  OscManager.cpp
 *  Llum 2020 App
 *
 *  Created by Imanol Gomez on 07/02/20.
 *
 */




#include "OscManager.h"
#include "SettingsManager.h"
#include "AppManager.h"


const string OscManager::OSC_PARENT_ADDRESS = "/Llum2020";

OscManager::OscManager(): Manager()
{
    //Intentionally left empty
}

OscManager::~OscManager()
{
   ofLogNotice() << "OscManager::destructor";
}


//--------------------------------------------------------------

void OscManager::setup()
{
    if(m_initialized)
        return;
    
    Manager::setup();
    
    this->setupOscReceiver();
    //this->setupOscSender();
    
    ofLogNotice() <<"OscManager::initialized" ;
}

void OscManager::setupOscReceiver()
{
    int portReceive = AppManager::getInstance().getSettingsManager().getOscPortReceive();
   
    if(m_oscReceiver.setup(portReceive))
    {
         ofLogNotice() <<"OscManager::setupOscReceiver -> listening to port " << portReceive;
    }
    else{
        ofLogNotice() <<"OscManager::setupOscReceiver -> could not listen to port  " << portReceive;
    }
    
}

void OscManager::setupOscSender()
{
    int portSend = AppManager::getInstance().getSettingsManager().getOscPortSend();
    string host = AppManager::getInstance().getSettingsManager().getIpAddress();
    m_oscSender.setup(host, portSend);
    ofLogNotice() <<"OscManager::setupOscSender -> open osc connection " << host << ":" << portSend;
    
}



void OscManager::update()
{
    // check for waiting messages
    while(m_oscReceiver.hasWaitingMessages())
    {
        // get the next message
        ofxOscMessage m;
        m_oscReceiver.getNextMessage(m);
        
        if(m.getAddress() == OSC_PARENT_ADDRESS + "/Scene")
        {
            int value = m.getArgAsInt(0);
            AppManager::getInstance().getGuiManager().onSceneChange(value);
        }
          
        else if(m.getAddress() == OSC_PARENT_ADDRESS + "/AudioLow")
        {
            float value = m.getArgAsFloat(0);
            AppManager::getInstance().getGuiManager().setAudioLow(value);
        }
		else if (m.getAddress() == OSC_PARENT_ADDRESS + "/AudioMid")
		{
			float value = m.getArgAsFloat(0);
			AppManager::getInstance().getGuiManager().setAudioMid(value);
		}
		else if (m.getAddress() == OSC_PARENT_ADDRESS + "/AudioHigh")
		{
			float value = m.getArgAsFloat(0);
			AppManager::getInstance().getGuiManager().setAudioHigh(value);
		}
		else if (m.getAddress() == OSC_PARENT_ADDRESS + "/AudioLowOnset")
		{
			bool value = m.getArgAsInt(0)>0;
			AppManager::getInstance().getGuiManager().setAudioLowOnset(value);
		}
		else if (m.getAddress() == OSC_PARENT_ADDRESS + "/AudioMidOnset")
		{
			bool value = m.getArgAsInt(0) > 0;
			AppManager::getInstance().getGuiManager().setAudioMidOnset(value);
		}

		else if (m.getAddress() == OSC_PARENT_ADDRESS + "/AudioHighOnset")
		{
			bool value = m.getArgAsInt(0) > 0;
			AppManager::getInstance().getGuiManager().setAudioHighOnset(value);
		}

        
        //int portReceive = AppManager::getInstance().getSettingsManager().getOscPortReceive();
        //string text = "OSC Receive (port: " +  ofToString(portReceive) + ")-> " + this->getMessageAsString(m);
        
        //ofLogNotice() << text;
    }
}

void OscManager::draw()
{
   
}

string OscManager::getMessageAsString(const ofxOscMessage& m) const
{
    string msg_string;
    msg_string = m.getAddress();
    for(int i = 0; i < m.getNumArgs(); i++){
        // get the argument type
        msg_string += " ";
        // display the argument - make sure we get the right type
        if(m.getArgType(i) == OFXOSC_TYPE_INT32){
            msg_string += ofToString(m.getArgAsInt32(i));
        }
        else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
            msg_string += ofToString(m.getArgAsFloat(i));
        }
        else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
            msg_string += m.getArgAsString(i);
        }
        else{
            msg_string += "unknown";
        }
    }
    
    return msg_string;
}










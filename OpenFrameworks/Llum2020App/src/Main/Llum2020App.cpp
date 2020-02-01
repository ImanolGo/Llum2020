/*
 *  Llum2020App.cpp
 *  Llum 2020 App
 *
 *  Created by Imanol Gomez on 01/02/20.
 *
 */



#include "AppManager.h"

#include "Llum2020App.h"

//--------------------------------------------------------------
void Llum2020App::setup(){
    AppManager::getInstance().setup();
}

//--------------------------------------------------------------
void Llum2020App::update(){
    AppManager::getInstance().update();
}

//--------------------------------------------------------------
void Llum2020App::draw(){
    AppManager::getInstance().draw();
}

void Llum2020App::exit()
{
    ofLogNotice() <<"Llum2020App::exit";

}

//--------------------------------------------------------------
void Llum2020App::keyPressed(int key){

}

//--------------------------------------------------------------
void Llum2020App::keyReleased(int key){

}

//--------------------------------------------------------------
void Llum2020App::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void Llum2020App::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void Llum2020App::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void Llum2020App::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void Llum2020App::windowResized(int w, int h){
    AppManager::getInstance().getLayoutManager().windowResized(w,h);


}

//--------------------------------------------------------------
void Llum2020App::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void Llum2020App::dragEvent(ofDragInfo dragInfo){

}

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(27,158,132);
    drawToBuffer();
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::drawToBuffer(){
    img.load("cheetah.png");
    img.setImageType(OF_IMAGE_GRAYSCALE);
    
    buffer.allocate(ofGetWidth(), ofGetHeight());
    buffer.begin();
    
    for(int i=0; i<img.getWidth(); i+=20) {
        for(int j=0; j<img.getHeight(); j+=20){
            ofColor c  = img.getColor(i,j);
            float brightness = c.getBrightness();
            ofPushMatrix();
            ofTranslate(i, j);
            float brightnessAsMorse = ofMap(brightness,0,255,0,20);
            float brightnessAsBlue = ofMap(brightness,0,255,170,255);

            float newValue;
            
            if (brightnessAsMorse > 2){
                newValue = 3;
            }
            if (brightnessAsMorse > 13){
                newValue = 15;
            }


            int furthestPossibleStart = 18-newValue;
            ofSetColor(brightnessAsBlue, 158, 132);
            ofDrawRectangle(ofRandom(2, furthestPossibleStart), 0, newValue, 10);
            ofPopMatrix();
        }
    }
    
    buffer.end();
}

//--------------------------------------------------------------
void ofApp::draw(){
    buffer.draw(0,0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

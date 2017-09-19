#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

}

//--------------------------------------------------------------
void ofApp::update(){

}


//--------------------------------------------------------------
void ofApp::draw(){
    // www.galeriecourcarree.com/img/galeries/vera_molnar/web/Galerie-Cour-Carree-Vera-Molnar-8.jpeg
    
    ofBackground(255);
    ofSetColor(0);
    ofSeedRandom(0);
    
    int columns = 60;
    int rows = 25;
    
    float midpoint = floor(columns/2);
    int offset = 20;
    int cellSize = 20;
    float angleVariation = 10.0;
    int minAngle = 90;
    
    for (int i=0;i<columns;i++){
        int distanceFromCenter = abs(i - midpoint);
        float distanceFromEdge = midpoint - distanceFromCenter;
        
        float maxAngle;
        if(distanceFromEdge == 0) {
            maxAngle = minAngle;
        } else {
            maxAngle = minAngle + (angleVariation*(distanceFromEdge/7.0));
        }
        
        for (int j=0;j<rows;j++){
            int xPos = i*cellSize;
            int yPos = j*cellSize;
            
            float xOffset = offset/distanceFromEdge;
            ofPoint pos = ofPoint(xPos-xOffset, yPos+offset);
            
            ofPushMatrix();
            
            ofTranslate(pos.x, pos.y);
            ofRotateZ(ofRandom(minAngle, maxAngle));
            ofPoint a = -ofPoint(0, cellSize);
            ofPoint b = ofPoint(cellSize,0);
            ofSetLineWidth(distanceFromEdge/3);
            ofDrawLine(a,b);
            
            ofPopMatrix();
        }
    }
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

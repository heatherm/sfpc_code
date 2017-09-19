#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // www.galeriecourcarree.com/img/galeries/vera_molnar/web/Galerie-Cour-Carree-Vera-Molnar-8.jpeg
    
    columns = 60;
    rows = 25;
    midPoint = floor(columns/2);
    cellSize = 20;
    minAngle = 90;
    
    ofBackground(255);
    ofSetColor(0);
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSeedRandom(0);
}

//--------------------------------------------------------------
void ofApp::drawLineWithAngleAndThickness(ofPoint startingPoint, int angleVariation, int distanceFromEdge){
    int maxAngle = minAngle + angleVariation;
    
    ofTranslate(startingPoint.x, startingPoint.y);
    ofRotateZ(ofRandom(minAngle, maxAngle));
    ofPoint lineStart = -ofPoint(0, cellSize);
    ofPoint lineEnd = ofPoint(cellSize,0);
    ofSetLineWidth(distanceFromEdge/3);
    ofDrawLine(lineStart, lineEnd);
}

//--------------------------------------------------------------
int ofApp::calculateAngleRangeForColumn(int columnPosition){
    float distanceFromEdge = midPoint - abs(columnPosition - midPoint);
    
    if(distanceFromEdge == 0) {
        return 0;
    } else {
        return 10.0*(distanceFromEdge/7.0);
    }
}

//--------------------------------------------------------------
ofPoint ofApp::calculateStartCoordinates(int columnPosition, int rowPosition){
    float distanceFromEdge = midPoint - abs(columnPosition - midPoint);
    
    int xPos = columnPosition*cellSize;
    int yPos = rowPosition*cellSize;
    
    float xOffset = offset/distanceFromEdge;
    ofPoint pos = ofPoint(xPos-xOffset, yPos+offset);
    return pos;
}

//--------------------------------------------------------------
void ofApp::draw(){
    for (int column=0;column<columns;column++){
        int possibleAngleVariation = calculateAngleRangeForColumn(column);

        for (int row=0;row<rows;row++){
            ofPoint lineStart = calculateStartCoordinates(column, row);

            ofPushMatrix();
            int distanceFromEdge = midPoint - abs(column - midPoint);
            drawLineWithAngleAndThickness(lineStart, possibleAngleVariation, distanceFromEdge);
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

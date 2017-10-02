#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    soundPlayer.load("sounds/taro.mp3");
    soundPlayer.play();
        
    ofSetVerticalSync(true);
    ofBackground(0);
    
    int bufferSize = 256;
    
    left.assign(bufferSize, 0.0);
    right.assign(bufferSize, 0.0);
    
    bufferCounter	= 0;
    drawCounter		= 0;
    smoothedVol     = 0.0;
    scaledVol		= 0.0;
    
        
    ofSoundStreamSetup(0, 2, this, 44100, bufferSize, 2);
    
    auto devices = soundStream.getMatchingDevices("default");
    if(!devices.empty()){
        soundStream.setDevice(devices[0]);
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    ofScopedLock waveformLock(mutex);
    
    scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(225);
    
    ofNoFill();

    ofPushStyle();
    ofPushMatrix();
    ofTranslate(0, 0, 0);
    
    ofSetColor(225);
    ofDrawBitmapString("Scaled average vol (0-100): " + ofToString(scaledVol * 100.0, 0), 4, 18);
    
    ofFill();
    
    float time = ofGetElapsedTimef();
    ofSetCircleResolution(100);
    for (size_t i = 0 ; i < ofGetWidth(); i++){
        ofSetColor(
                   102,
                   178+77*cos(ofGetElapsedTimef()+ i*0.013),
                   178+77*cos(ofGetElapsedTimef()+ (i*0.014))
                   );

        ofDrawCircle(i, ofGetHeight()/2 + (scaledVol * 290.0f) *sin(i*.03+time*1.4), 60+40*sin(i*0.01 + time));
    }
    
    
    ofPopMatrix();
    ofPopStyle();

    drawCounter++;
    
}

//--------------------------------------------------------------
void ofApp::audioIn(ofSoundBuffer & input){
    ofScopedLock waveformLock(mutex);
    
    float curVol = 0.0;
    
    int numCounted = 0;
    
    for (size_t i = 0; i < input.getNumFrames(); i++){
        left[i]		= input[i*2]*0.5;
        right[i]	= input[i*2+1]*0.5;
        
        curVol += left[i] * left[i];
        curVol += right[i] * right[i];
        numCounted+=2;
    }
    
    curVol /= (float)numCounted;
    
    curVol = sqrt( curVol );
    
    smoothedVol *= 0.93;
    smoothedVol += 0.07 * curVol;
    
    bufferCounter++;
}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key){
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

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    gui.setup();
    gui.add(range.setup("range", 40, 10, 50));
    gui.add(smoothScale.setup("smoothScale", .9, .89, .9999));

    
    nTri = 256;
    nVert = nTri * 3;
    float Rad = 250;
    float rad = 25;
    vertices.resize( nVert );
    for (int i=0; i< nTri; i++) {
        ofPoint center( ofRandom( -1, 1 ), ofRandom( -1, 1 ), ofRandom( -1, 1 ) );
        center.normalize();
        center *= Rad;
        for (int j=0; j<3; j++) {
            vertices[ i*3 + j ] = center + ofPoint( ofRandom( -rad, rad ), ofRandom( -rad, rad ), ofRandom( -rad, rad ) ); }
    }
    colors.resize( nTri );
    for (int i=0; i<nTri; i++) {
        colors[i] = ofColor( 0, ofRandom( 0, 255 ), 0 );
    }
    
    player.load("sounds/taro.mp3");
    
    fftSmooth = new float [8192];
    for (int i = 0; i < 8192; i++){
        fftSmooth[i] = 0;
    }
    
    bands = 128;
    player.setLoop(true);
    player.setVolume(0.5);
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSoundUpdate();
    
    float *  value  = ofSoundGetSpectrum(bands);
    for (int i = 0; i < bands; i++){
        fftSmooth[i] *= smoothScale;
        if (fftSmooth[i] < value[i]){
            fftSmooth[i] = fftSmooth[i]*smoothScale+value[i]*(1-smoothScale);
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    
    ofEnableDepthTest();
    ofBackgroundGradient( ofColor( 128 ), ofColor( 0 ) );

    ofPushMatrix();
    
    float time = ofGetElapsedTimef();
    ofTranslate( ofGetWidth()/2, ofGetHeight()/2, 0 );
    float angle = sin(time);
    ofRotate( angle, 0, 1, 0 );
    
    for (int i=0; i<nTri; i++) {
        ofSetColor( colors[i] );
        float vertScale = fftSmooth[i]*range;
        ofDrawTriangle(
                       vertices[ i*3 ]*-(vertScale),
                       vertices[ i*3 + 1 ]*-(vertScale),
                       vertices[ i*3 + 2 ]*-(vertScale)
                       );
    }
    
    ofPopMatrix();
    
    
    ofDisableDepthTest();
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key){
        case 'a':
            player.play();
            break;
        case 's':
            player.stop();
            break;
    }
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

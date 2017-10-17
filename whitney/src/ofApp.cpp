#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    gui.setup();
    gui.add(scaleFactor.setup("scaleFactor", 0.1, 10, .3));
    
//    soundPlayer.load("sounds/taro.mp3");
//    soundPlayer.play();
    
    int bufferSize = 256;
    left.assign(bufferSize, 0.0);
    right.assign(bufferSize, 0.0);
    smoothedVol     = 0.0;
    scaledVol		= 0.0;
    
    
    ofSoundStreamSetup(0, 2, this, 44100, bufferSize, 2);
    
    auto devices = soundStream.getMatchingDevices("default");
    if(!devices.empty()){
        soundStream.setDevice(devices[0]);
    }
    
    soundStream.printDeviceList();
    
    decayRate = 0.05;
    minimumThreshold = 0.1;
    threshold = minimumThreshold;
    
    cameraRotation.set(0);
    zoom = -500;
    zoomTarget = 200;
    
    billboards.getVertices().resize(NUM_BILLBOARDS);
    billboards.getColors().resize(NUM_BILLBOARDS);
    billboards.getNormals().resize(NUM_BILLBOARDS,ofVec3f(0));
    
    for (int i=0; i<NUM_BILLBOARDS; i++) {
        billboardVels[i].set(ofRandomf(), -1.0, ofRandomf());
        billboards.getVertices()[i] = {ofRandom(-500, 500),ofRandom(-500, 500),ofRandom(-500, 500)};
        
        billboards.getColors()[i].set(ofColor::fromHsb(ofRandom(0, 45), 255, 255));
        billboardSizeTarget[i] = ofRandom(15, 100);
    }
    
    billboards.setUsage(GL_DYNAMIC_DRAW);
    billboards.setMode(OF_PRIMITIVE_POINTS);
    billboardShader.load("shadersGL2/Billboard");

    ofDisableArbTex();
    texture.load("spark.png");
    ofEnableAlphaBlending();
}

//--------------------------------------------------------------
void ofApp::update() {
    ofScopedLock waveformLock(mutex);
    
    scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);
    
    float t = (ofGetElapsedTimef()) * 0.9f;
    float div = 250.0;
    
    for (int i=0; i<NUM_BILLBOARDS; i++) {
        ofVec3f vec(ofSignedNoise(t, billboards.getVertex(i).y/div, billboards.getVertex(i).z/div),
                    ofSignedNoise(billboards.getVertex(i).x/div, t, billboards.getVertex(i).z/div),
                    ofSignedNoise(billboards.getVertex(i).x/div, billboards.getVertex(i).y/div, t));
        
        vec *= 10 * ofGetLastFrameTime();
        billboardVels[i] += vec;
        billboards.getVertices()[i] += billboardVels[i];
        billboardVels[i] *= 0.94f;
        billboards.setNormal(i,ofVec3f(12 + billboardSizeTarget[i] * ofNoise(t+i),0,0));
    }
    
    float mx = (float)scaledVol*scaleFactor/(float)ofGetWidth();
    float my = (float)scaledVol*scaleFactor/(float)ofGetHeight();
    ofVec3f des(mx * 360.0, my * 360.0, 0);
    cameraRotation += scaledVol*3;

    zoom += (zoomTarget - zoom) * scaleFactor*scaledVol;
//    soundPlayer.setSpeed(ofRandom(0.8, 1.2));
    
    
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofBackgroundGradient(ofColor(255,255,0), ofColor(255,0,0));
    
    gui.draw();

    ofSetColor(255);
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2, zoom);
    ofRotate(cameraRotation.x, 1, 0, 0);
    ofRotate(cameraRotation.y, 0, 1, 0);
    ofRotate(cameraRotation.y, 0, 0, 1);
    

    billboardShader.begin();
    
    ofEnablePointSprites(); // for GL2
    texture.getTexture().bind();
    billboards.draw();
    texture.getTexture().unbind();
    ofDisablePointSprites(); // for GL2
    
    billboardShader.end();
    
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::audioIn(ofSoundBuffer & input){
    ofScopedLock waveformLock(mutex);
    
    threshold = ofLerp(threshold, minimumThreshold, decayRate);
    
    
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
    
    if(curVol > threshold) {
        curVol = curVol*0.7+threshold*(.3);

        threshold = curVol;
    }
    
    smoothedVol *= 0.93;
    smoothedVol += 0.07 * curVol;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'f') ofToggleFullscreen();
    if(key == OF_KEY_UP) zoomTarget +=10;
    if(key == OF_KEY_DOWN) zoomTarget -=10;
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
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

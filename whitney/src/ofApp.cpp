#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(false);
    ofSetFrameRate(30);
    
    pm.setup(1024*1024);

    gui.setup();
    gui.add(pm.parameters);
    gui.add(fpsDisp.setup("Fps", ""));
    gui.add(scaleFactor.setup("scaleFactor", 100, 400, 10));
    
    bSettings = false;
    bPause = false;
    
//    soundPlayer.load("sounds/taro.mp3");
//    soundPlayer.play();
    
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
//    ofScopedLock waveformLock(mutex);
    
    fpsDisp = ofToString(ofGetFrameRate());
    
    if(!bPause){
        pm.update();
    }
    
    scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(225);
    if(bSettings){
        gui.draw();
    }else{
        ofSetColor(ofColor::white);
        ofDrawBitmapString("'s' settings\n'p' pause\n'f' fullscreen", 15, 15);
    }
    ofNoFill();

    ofPushStyle();
    ofPushMatrix();
    ofTranslate(0, 0, 0);
    
    ofSetColor(225);

    ofDrawBitmapString("Scaled average vol (0-100): " + ofToString(scaledVol * 100.0, 0), 4, 18);
    
    ofFill();
    
//    float time = ofGetElapsedTimef();
//    ofSetCircleResolution(100);
//    for (size_t i = 0 ; i < ofGetWidth(); i++){
//        ofSetColor(
//                   102,
//                   178+77*cos(ofGetElapsedTimef()+ i*0.013),
//                   178+77*cos(ofGetElapsedTimef()+ (i*0.014))
//                   );
//
//        ofDrawCircle(
//                     i,
//                     ofGetHeight()/2 + (scaledVol * scaleFactor) * sin(i*.03+time*1.4),
//                     60+40*sin(i*0.01 + time)
//                     );
//    }
    
    cam.begin();
    pm.draw();
    cam.end();
    
    ofPopMatrix();
    ofPopStyle();

    drawCounter++;
    
}

void ofApp::drawSpiral(double a,double b)
{
    double x, y;
    
    int theta = 0;
    x = a*pow(2.718281,(double)b*theta)*cos(theta);
    y = a*pow(2.718281,(double)b*theta)*sin(theta);
    for (int i = 0; i < 1000; i++)
    {
        glBegin(GL_LINES);
        theta = 0.025*i;
        glVertex2f((GLfloat)x, (GLfloat)y);
        glVertex2f(a*pow(2.718281, (double)b*theta)*cos(theta), a*pow(2.718281, (double)b*theta)*sin(theta));
        
        //glColor3f(r, g, b);
        x = a*pow(2.718281, (double)b*theta)*cos(theta);
        y = a*pow(2.718281, (double)b*theta)*sin(theta);
        
        glEnd();
    }
    
}



//--------------------------------------------------------------
void ofApp::audioIn(ofSoundBuffer & input){
//    ofScopedLock waveformLock(mutex);
    
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
    switch(key){
        case 'f':
            ofToggleFullscreen();
            break;
        case 's':
            bSettings = !bSettings;
            break;
        case 'p':
            bPause = !bPause;
            break;
        default:
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

#pragma once
#include "ofMain.h"
#include "ofVbo.h"
#include "ofxGui.h"

#define NUM_BILLBOARDS 600

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    // billboard
    ofVec3f cameraRotation;
    float zoom, zoomTarget;
    float billboardSizeTarget[NUM_BILLBOARDS];
    ofShader billboardShader;
    ofImage texture;
    ofVboMesh billboards;
    ofVec3f billboardVels[NUM_BILLBOARDS];
    
    // audio
    void audioIn(ofSoundBuffer & input);
    
    vector <float> left;
    vector <float> right;
    vector <float> volHistory
    int bufferCounter;
    float smoothedVol;
    float scaledVol;
    ofSoundStream soundStream;
    ofSoundPlayer soundPlayer;
    ofMutex mutex;
    
    // gui
    ofxPanel gui;
    ofxFloatSlider scaleFactor;
};
